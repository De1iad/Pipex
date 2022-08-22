/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:43:24 by obibby            #+#    #+#             */
/*   Updated: 2022/02/23 20:43:24 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str1, const char *str2, size_t n)
{
	size_t	i;
	size_t	i2;
	size_t	x;

	i = 0;
	i2 = 0;
	x = 0;
	if (str2[0] == '\0')
		return ((char *)str1);
	while (i < n && str1[i] != '\0')
	{
		i2 = i;
		while (str2[x] == str1[i2] && i2 < n)
		{
			x++;
			if (str2[x] == '\0')
				return ((char *)(str1 + (i2 + 1 - x)));
			i2++;
		}
		x = 0;
		i++;
	}
	return (NULL);
}
