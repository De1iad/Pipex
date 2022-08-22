/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 23:50:00 by obibby            #+#    #+#             */
/*   Updated: 2022/02/24 23:50:00 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Allocates and returns an array of strings by splitting s using delimiter c.

static int	w_counter(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count + 1);
}

static int	c_counter(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len++;
		i++;
	}
	return (len);
}

static char	**allfree(char **arr1, int x)
{
	int	i;

	i = 0;
	while (x > 0)
	{
		free(arr1[i]);
		i++;
		x--;
	}
	free(arr1);
	return (NULL);
}

static char	**makestr(char **arr1, char const *s, char c)
{
	int		i;
	int		x;
	int		lc;

	lc = 0;
	i = -1;
	x = 0;
	while (s[++i] != '\0')
	{
		lc = c_counter(s, c, i);
		if (lc > 0)
		{
			arr1[x] = malloc(sizeof(char) * (lc + 1));
			if (arr1[x] == NULL)
				return (allfree(arr1, x));
			ft_strlcpy(arr1[x++], s + i, lc + 1);
			i = i + lc - 1;
		}
	}
	arr1[x] = NULL;
	return (arr1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr1;

	if (s == NULL)
		return (NULL);
	arr1 = malloc(sizeof(char *) * (w_counter(s, c)));
	if (arr1 == NULL)
		return (NULL);
	makestr(arr1, s, c);
	return (arr1);
}
