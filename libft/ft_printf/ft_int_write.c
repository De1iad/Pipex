/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_int_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:14:09 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:20:06 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	check_negative(char *flags)
{
	int	negative;
	int	count;

	negative = 0;
	count = flags[3];
	while (count-- > 0)
		negative += 1;
	return (negative % 2);
}

int	print_int(char *str, char *flags, int width, int prec)
{
	int	charno;
	int	i;

	charno = 0;
	i = 0;
	while (flags[6] == 0 && ((flags[5] == 0) | (flags[1] != 0)) && width-- > 0)
		charno += write(1, " ", 1);
	if (check_negative(flags) != 0 && str[0] != '-')
		charno += write(1, "+", 1);
	else if (str[0] == '-' && str[i++] == '-')
		charno += write(1, "-", 1);
	else if (flags[2] != 0 && str[0] != '-' && check_negative(flags) == 0)
		charno += write(1, " ", 1);
	while (flags[6] == 0 && flags[5] != 0 && flags[1] == 0 && width-- > 0)
		charno += write(1, "0", 1);
	while (prec-- > (int)ft_strlen(str + i))
		charno += write(1, "0", 1);
	while (str[i] && (str[0] != '0' || prec != -1 || flags[0] + flags[1] == 0))
		charno += write(1, &str[i++], 1);
	while (flags[6] != 0 && width-- > 0)
		charno += write(1, " ", 1);
	return (charno);
}

int	ft_int_write(va_list vl, char *flags, int width, int prec)
{
	long long	n;
	char		*str;
	int			charno;

	n = va_arg(vl, long long);
	str = ft_itoa(n);
	charno = 0;
	if (flags[7] == '*')
		width = va_arg(vl, int);
	if (flags[0] == '*')
		prec = va_arg(vl, int);
	if (prec >= (int)ft_strlen(str))
	{
		width -= prec;
		if (str[0] == '-' || check_negative(flags) != 0 || flags[2] != 0)
			width--;
	}
	else if (str[0] != '0' || prec != 0 || flags[0] + flags[1] == 0)
		width -= (int)ft_strlen(str);
	charno += print_int(str, flags, width, prec);
	free(str);
	return (charno);
}
