/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flag_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 00:25:01 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:19:27 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_bzero_printf(char *str, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n - 1)
		str[i++] = 0;
}

int	char_count_dec(long x)
{
	int	count;

	count = 0;
	if (x == 0)
		return (1);
	while (x != 0)
	{
		x = x / 10;
		count++;
	}
	return (count);
}

void	ft_flag_count(char *flags, int width, int prec)
{
	int	i;

	i = 0;
	while (i < 17)
	{
		flags[17] += flags[i];
		i++;
	}
	if (flags[7] != 0)
		flags[17] += char_count_dec(width) - 1;
	if (flags[0] != 0)
		flags[17] += 1;
	if (flags[1] != 0)
		flags[17] += char_count_dec(prec);
	return ;
}
