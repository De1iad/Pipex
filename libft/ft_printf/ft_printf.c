/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 19:37:57 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:20:10 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// calls write function depending on type.

int	ft_writer(va_list vl, char *flags, int width, int prec)
{
	if (flags[16] == 1)
		return (write(1, "%", 1));
	if (flags[15] == 1 || flags [14] == 1)
		return (ft_hexa_write(vl, flags, width, prec));
	if (flags[13] == 1)
		return (ft_uint_write(vl, flags, width, prec));
	if (flags[12] == 1 || flags[11] == 1)
		return (ft_int_write(vl, flags, width, prec));
	if (flags[10] == 1)
		return (ft_ptr_write(vl, flags, width));
	if (flags[9] == 1)
		return (ft_str_write(vl, flags, width, prec));
	if (flags[8] == 1)
		return (ft_char_write(vl, flags, width));
	return (0);
}

// sets flag depending on type to be converted.

void	conver_type(const char *s, char *flags)
{
	if (s[0] == 'c')
		flags[8] = 1;
	if (s[0] == 's')
		flags[9] = 1;
	if (s[0] == 'p')
		flags[10] = 1;
	if (s[0] == 'd')
		flags[11] = 1;
	if (s[0] == 'i')
		flags[12] = 1;
	if (s[0] == 'u')
		flags[13] = 1;
	if (s[0] == 'x')
		flags[14] = 1;
	if (s[0] == 'X')
		flags[15] = 1;
	if (s[0] == '%')
		flags[16] = 1;
	return ;
}

// checks for and sets flags.

void	ft_flag_check(const char *s, char *flags, int i)
{
	while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'd'
		&& s[i] != 'i' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X'
		&& s[i] != '%')
	{
		if (s[i] == '.' && s[i + 1] == '*')
			flags[0] = 1;
		if (s[i] == '.')
			flags[1] = 1;
		if (s[i] == ' ')
			flags[2] += 1;
		if (s[i] == '+')
			flags[3] += 1;
		if (s[i] == '#')
			flags[4] = 1;
		if (s[i] == '0' && flags[7] == 0 && flags[1] == 0)
			flags[5] += 1;
		if (s[i] == '-')
			flags[6] += 1;
		if (((s[i] > '0' && s[i] <= '9' && (s[i - 1] <= '0' || s[i - 1] > '9'))
				|| s[i] == '*') && (s[i - 1] != '.' || i == 0))
			flags[7] = 1;
		i++;
	}
	return ;
}

// prepares arguments for writing.

int	ft_print_arg(const char *s, va_list vl, char *flags)
{
	int	i;
	int	width;
	int	prec;

	i = 0;
	width = 0;
	prec = 0;
	ft_flag_check(s, flags, i);
	while (s[i] != 'c' && s[i] != 's' && s[i] != 'p' && s[i] != 'd'
		&& s[i] != 'i' && s[i] != 'u' && s[i] != 'x' && s[i] != 'X'
		&& s[i] != '%')
	{
		if (s[i] > '0' && s[i] <= '9' && (s[i - 1] <= '0' || s[i - 1] > '9'
				|| i == 0) && s[i - 1] != '.' && width == 0)
			width = ft_atoi(s + i);
		if (s[i] == '.' && s[i + 1] <= '9' && s[i + 1] >= '0')
			prec = ft_atoi(s + i++ + 1);
		if (s[i] == '.' && (s[i + 1] > '9' || (s[i + 1] < '0'
					&& s[i + 1] != '*')))
			flags[17] -= 1;
		i++;
	}
	conver_type(s + i, flags);
	ft_flag_count(flags, width, prec);
	return (ft_writer(vl, flags, width, prec));
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		writeno;
	char	*flags;
	va_list	vl;

	i = -1;
	writeno = 0;
	flags = ft_calloc(19, sizeof(char));
	va_start(vl, str);
	while (str[++i])
	{
		if (str[i] != '%')
			writeno += write(1, &str[i], 1);
		if (str[i] == '%')
		{
			ft_bzero_printf(flags, 19);
			writeno += ft_print_arg(str + i + 1, vl, flags);
			flags[17] = flags[17] + i;
			while (str[i + 1] && i < flags[17])
				i++;
		}
	}
	va_end(vl);
	free(flags);
	return (writeno);
}
