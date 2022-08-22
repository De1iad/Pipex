/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 22:17:04 by obibby            #+#    #+#             */
/*   Updated: 2022/02/24 22:17:04 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		x;
	char	*ptr;

	if (s1 == NULL || set == NULL)
		return (NULL);
	i = 0;
	x = ft_strlen(s1);
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	while (ft_strchr(set, s1[x]) && x > i)
		x--;
	ptr = ft_substr(s1, i, x + 1 - i);
	return (ptr);
}
