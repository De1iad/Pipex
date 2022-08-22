/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:12:36 by obibby            #+#    #+#             */
/*   Updated: 2022/02/23 21:12:36 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	int		destlen;
	int		srclen;

	i = 0;
	destlen = ft_strlen(dest);
	srclen = ft_strlen(src);
	while (dest[i] != '\0')
	{
		if (i == size)
			return (size + srclen);
		i++;
	}
	while (src[i - destlen] != '\0' && i < size - 1 && size > 0)
	{
		dest[i] = src[i - destlen];
		i++;
	}
	dest[i] = '\0';
	return (destlen + srclen);
}
