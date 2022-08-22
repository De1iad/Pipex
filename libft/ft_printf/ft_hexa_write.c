/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexa_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 14:54:10 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:20:01 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	width_write_hex(int width, char *flags, int x)
{
	int	charno;

	charno = 0;
	if (flags[6] == 0 && (flags[0] + flags[1] != 0 || flags[5] == 0))
	{
		while (width-- > 0)
			charno += write(1, " ", 1);
	}
	if (flags[4] == 1 && flags[14] == 1 && x != 0)
		charno += write(1, "0x", 2);
	if (flags[4] == 1 && flags[15] == 1 && x != 0)
		charno += write(1, "0X", 2);
	if (flags[5] != 0 && flags[6] + flags[1] + flags[0] == 0)
	{
		while (width-- > 0)
			charno += write(1, "0", 1);
	}
	return (charno);
}

int	hexa_conv(long x, char *flags)
{
	char	hexastr[100];
	long	rem;
	int		i;
	int		charno;

	rem = 0;
	i = 0;
	charno = 0;
	while (x != 0)
	{
		rem = x % 16;
		if (rem < 10)
			hexastr[i++] = rem + '0';
		else if (flags[15] == 1)
			hexastr[i++] = rem + '7';
		else
			hexastr[i++] = rem + 'W';
		x = x / 16;
	}
	i -= 1;
	while (i >= 0)
		charno += write(1, &hexastr[i--], 1);
	return (charno);
}

int	char_count_hex(unsigned int x)
{
	int	count;

	count = 0;
	if (x == 0)
		return (1);
	while (x != 0)
	{
		x = x / 16;
		count++;
	}
	return (count);
}

int	ft_hexa_write(va_list vl, char *flags, int width, int prec)
{
	unsigned int	x;
	int				count;
	int				charno;

	x = va_arg(vl, int);
	count = char_count_hex(x);
	charno = 0;
	if (flags [4] == 1 && x != 0)
		width -= 2;
	if (flags[1] == 1 && prec > count)
		width -= prec;
	else if (x != 0 || flags[1] == 0 || prec != 0)
		width -= count;
	charno += width_write_hex(width, flags, x);
	while (count < prec--)
		charno += write(1, "0", 1);
	if (x == 0 && (flags[1] == 0 || prec != -1))
		charno += write(1, "0", 1);
	else
		charno += hexa_conv(x, flags);
	while (flags[6] != 0 && width-- > 0)
		charno += write(1, " ", 1);
	return (charno);
}
