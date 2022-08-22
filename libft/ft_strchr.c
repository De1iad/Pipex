/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 15:02:43 by obibby            #+#    #+#             */
/*   Updated: 2022/01/19 15:45:32 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	if (c > 255)
		c -= 256;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (&((char *)str)[i]);
		i++;
	}
	if (str[i] == c)
		return (&((char *)str)[i]);
	return (NULL);
}
