/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:23:10 by obibby            #+#    #+#             */
/*   Updated: 2022/01/19 15:42:35 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int	i;
	int	l;

	i = 0;
	l = -1;
	if (c > 255)
		c -= 256;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			l = i;
		i++;
	}
	if (l != -1)
		return (&((char *)str)[l]);
	if (str[i] == c)
		return (&((char *)str)[i]);
	return (NULL);
}
