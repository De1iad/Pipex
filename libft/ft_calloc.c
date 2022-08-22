/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:36:05 by obibby            #+#    #+#             */
/*   Updated: 2022/02/23 21:36:05 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elenum, size_t size)
{
	void	*ptr;

	ptr = malloc(elenum * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, elenum * size);
	return (ptr);
}
