/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 11:44:02 by obibby            #+#    #+#             */
/*   Updated: 2022/08/22 00:26:54 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr_exit(t_cmd *cmds, int arr_num, void	*ptr, char *str)
{
	while (arr_num-- > 0)
		free(cmds->cmds[arr_num]);
	free(cmds->prog);
	if (ptr)
		free(ptr);
	error_exit(cmds->info->infile_no, cmds->info->outfile_no, str);
}

void	alloc_arr(char *str, t_cmd *cmds, t_info *info)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	cmds->cmds = ft_calloc(cmds->total + 1, sizeof(char *));
	if (!cmds->cmds)
		free_arr_exit(cmds, 0, NULL, "Memory allocation fail.");
	cmds->cmds[k] = ft_calloc(ft_strlen(cmds->prog) + 1, sizeof(char));
	if (!cmds->cmds[k])
		free_arr_exit(cmds, k, NULL, "Memory allocation fail.");
	i = -1;
	while (cmds->prog[++i])
		cmds->cmds[k][i] = cmds->prog[i];
	k++;
	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			j = i;
			while (str[j] && str[j] != ' ')
				j++;
			cmds->cmds[k] = ft_calloc((j - i) + 1, sizeof(char));
			if (!cmds->cmds[k])
				free_arr_exit(cmds, k, NULL, "Memory allocation fail.");
			j = 0;
			while (str[i] && str[i] != ' ')
				cmds->cmds[k][j++] = str[i++];
			k++;
		}
		if (str[i] == ' ')
			i++;
	}
	if (info->done_ops == 0)
	{
		cmds->cmds[k] = ft_calloc(ft_strlen(info->infile) + 1, sizeof(char));
		if (!cmds->cmds[k])
			free_arr_exit(cmds, k, NULL, "Memory allocation fail.");
		i = -1;
		while (info->infile[++i])
			cmds->cmds[k][i] = info->infile[i];
	}
}

void	free_joined(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

char	*search_path(t_cmd *cmds, t_info *info)
{
	int		i;
	char	*str;
	char	**arr;

	i = 0;
	str = "PATH=";
	while (info->env[i])
	{
		if (ft_strncmp(str, info->env[i], 5) == 0)
			break ;
		i++;
	}
	arr = ft_split(info->env[i], ':');
	if (!arr)
		free_arr_exit(cmds, cmds->total, NULL, "Memory allocation fail.");
	i = 0;
	while (arr[i])
	{
		str = ft_strjoin(arr[i++], cmds->prog);
		if (!str)
		{
			free_joined(arr);
			free_arr_exit(cmds, cmds->total, NULL, "Memory allocation fail.");
		}
		if (access(str, F_OK) == 0)
			break ;
		free(str);
		str = NULL;
	}
	free_joined(arr);
	return (str);
}

void	free_arr(t_cmd *cmds, void *ptr)
{
	while (cmds->total-- > 0)
		free(cmds->cmds[cmds->total]);
	free(cmds->prog);
	free(ptr);
}

void	exec_cmds(t_cmd *cmds, t_info *info)
{
	char	*path;
	int		pid;

	path = search_path(cmds, info);
	if (!path)
		free_arr_exit(cmds, cmds->total, NULL, "Command not found.");
	ft_printf("path: %s\n", path);											//path to prog
	ft_printf("%s, %s, %s\n", cmds->cmds[0], cmds->cmds[1], cmds->cmds[2]); //prog + flags
	if (access(path, X_OK) == -1)
		free_arr_exit(cmds, cmds->total, path, "Invalid permissions.");
	pid = fork();
	if (pid == 0)
	{
		close(info->in_now);
		dup2(info->out_now, STDOUT_FILENO);
		close(info->out_now);
		execve(path, cmds->cmds, info->env);
	}
	else
	{
		close(info->out_now);
		if (info->done_ops == 0)
		{
			close(info->in_now);
			info->in_now = info->pipe_fd[0];
		}
		dup2(info->in_now, STDIN_FILENO);
		close(info->in_now);
		waitpid(pid, NULL, 0);
	}
	free_arr(cmds, path);
}

void	read_input(char *str, t_info *info)
{
	int		i;
	int		j;
	t_cmd	cmds;

	i = 0;
	j = -1;
	cmds.info = info;
	cmds.total = 2;
	while (str[i] && str[i] != ' ')
		i++;
	cmds.prog = ft_calloc(i + 2, sizeof(char));
	if (!cmds.prog)
		error_exit(info->infile_no, info->outfile_no, "Memory allocation fail.");
	cmds.prog[0] = '/';
	while (++j < i)
		cmds.prog[j + 1] = str[j];
	if (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] != ' ')
		{
			cmds.total++;
			while (str[i] && str[i] != ' ')
				i++;
			if (str[i])
				i++;
		}
		else
			break ;
	}
	alloc_arr(&str[j], &cmds, info);
	exec_cmds(&cmds, info);
}

void	error_exit(int id1, int id2, char *str)
{
	if (id1 > 0)
		close(id1);
	if (id2 > 0)
		close(id2);
	ft_printf("%s\n", str);
	exit(1);
}

void	check_input(int	argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (++i < argc)
	{
		j = 0;
		while (argv[i][j] && ((argv[i][j] >= 'a' && argv[i][j] <= 'z')
			|| (argv[i][j] >= '0' && argv[i][j] <= '9') || (argv[i][j] >= 'A' && argv[i][j] <= 'Z')))
			j++;
		while (argv[i][j])
		{
			if (argv[i][j] == ' ' && argv[i][j + 1] == '-' && argv[i][j + 2] && ((argv[i][j + 2] >= 'a' && argv[i][j + 2] <= 'z')
				|| (argv[i][j + 2] >= '0' && argv[i][j + 2] <= 9) || (argv[i][j + 2] >= 'A' && argv[i][j + 2] <= 'Z')))
				j += 2;
			else
				error_exit(0, 0, "Invalid argument found.");
			while (argv[i][j] && ((argv[i][j] >= 'a' && argv[i][j] <= 'z')
				|| (argv[i][j] >= '0' && argv[i][j] <= '9') || (argv[i][j] >= 'A' && argv[i][j] <= 'Z')))
				j++;
		}
	}
}

void	out_file(char *file, t_info *info)
{
	int	i;

	i = 0;
	info->outfile_no = open(file, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (info->outfile_no == -1)
		error_exit(info->infile_no, 0, "Unable to create output file.");
	while (file[i])
		i++;
	info->outfile = ft_calloc(i + 1, sizeof(char));
	if (!info->outfile)
		error_exit(info->infile_no, info->outfile_no, "Memory allocation fail.");
	i = -1;
	while (file[++i])
		info->outfile[i] = file[i];
}

void	in_file(char *file, t_info *info)
{
	int	i;
	
	i = 0;
	info->infile_no = open(file, O_RDONLY);
	if (info->infile_no == -1)
		error_exit(0, 0, "Unable to read input file.");
	while (file[i])
		i++;
	info->infile = ft_calloc(i + 1, sizeof(char));
	if (!info->infile)
		error_exit(info->infile_no, 0, "Memory allocation fail.");
	i = -1;
	while (file[++i])
		info->infile[i] = file[i];
}

void	init_files(int argc, char **argv, t_info *info)
{
	in_file(argv[1], info);
	out_file(argv[argc - 1], info);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;

	if (argc < 3)
		error_exit(0, 0, "Wrong number of arguments.");
	//check_input(argc, argv);
	info.env = envp;
	info.total_ops = argc - 3;
	info.done_ops = 0;
	init_files(argc, argv, &info);
	while (info.done_ops < info.total_ops)
	{
		pipe(info.pipe_fd);
		info.out_now = info.pipe_fd[1];
		if (info.done_ops == 1)
			info.in_now = info.pipe_fd[0];
		if (info.done_ops + 1 == info.total_ops)
			info.out_now = info.outfile_no;
		read_input(argv[2 + info.done_ops], &info);
		info.done_ops++;
	}
	close(info.infile_no);
	close(info.outfile_no);
	free(info.infile);
	free(info.outfile);
	return (0);
}