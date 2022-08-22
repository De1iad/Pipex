/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:45:52 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:18:58 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_char_write(va_list vl, char *flags, int width)
{
	int		c;
	int		charno;

	c = va_arg(vl, int);
	charno = 0;
	if (flags[6] == 0 && width > 1)
	{
		while (width-- > 1)
			charno += write(1, " ", 1);
	}
	charno += write(1, &c, 1);
	if (flags[6] != 0 && width > 1)
	{
		while (width-- > 1)
			charno += write(1, " ", 1);
	}
	return (charno);
}
