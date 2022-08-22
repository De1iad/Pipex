/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 20:33:15 by obibby            #+#    #+#             */
/*   Updated: 2022/02/25 20:33:15 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	charcount(long long x)
{
	int	i;

	i = 0;
	if (x == 0)
		return (1);
	if (x < 0)
	{
		i++;
		x = -x;
	}
	while (x != 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long long	x;
	int			i;
	char		*str1;
	int			sign;

	x = n;
	sign = 0;
	i = charcount(x);
	if (x < 0)
	{
		x = -x;
		sign = 1;
	}
	str1 = malloc(sizeof(char) * (i + 1));
	if (str1 == NULL)
		return (NULL);
	str1[i] = '\0';
	while (i-- > sign)
	{
		str1[i] = (x % 10) + '0';
		x /= 10;
	}
	if (n < 0)
		str1[i] = '-';
	return (str1);
}
