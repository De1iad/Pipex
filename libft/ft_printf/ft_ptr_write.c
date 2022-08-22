/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ptr_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 12:37:52 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:20:14 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putptr(uintptr_t addr)
{
	char	hexastr[100];
	long	rem;
	int		i;
	int		charno;

	rem = 0;
	i = 0;
	charno = 0;
	while (addr != 0)
	{
		rem = addr % 16;
		if (rem < 10)
			hexastr[i++] = rem + '0';
		else
			hexastr[i++] = rem + 'W';
		addr = addr / 16;
	}
	i -= 1;
	while (i >= 0)
		charno += write(1, &hexastr[i--], 1);
	return (charno);
}

int	ft_ptr_count(uintptr_t p)
{
	int	count;

	count = 0;
	if (!p)
		return (3);
	while (p != 0)
	{
		p = p / 16;
		count++;
	}
	return (count);
}

int	ft_ptr_write(va_list vl, char *flags, int width)
{
	uintptr_t	addr;
	int			charno;

	addr = va_arg(vl, uintptr_t);
	charno = 0;
	width -= 2 + ft_ptr_count(addr);
	while (flags[6] == 0 && width-- > 0)
		charno += write(1, " ", 1);
	if (addr)
		charno += write(1, "0x", 2);
	else
		charno += write(1, "0x0", 3);
	charno += ft_putptr(addr);
	while (flags[6] != 0 && width-- > 0)
		charno += write(1, " ", 1);
	return (charno);
}
