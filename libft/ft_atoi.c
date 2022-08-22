/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:13:11 by obibby            #+#    #+#             */
/*   Updated: 2022/07/07 18:03:38 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		count;
	long	intstr;

	i = 0;
	intstr = 0;
	count = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\r'
		|| str[i] == '\n' || str[i] == '\v' || str[i] == '\f')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			count += 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
		intstr = (intstr * 10) + (str[i++] - '0');
	if (count % 2 != 0)
		intstr = -intstr;
	return (intstr);
}
