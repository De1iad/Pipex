/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_write.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 15:38:24 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:20:24 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putstr_printf(char *str, int prec, char *flags)
{
	int	i;

	i = 0;
	while (str[i] != 0 && (i < prec || (flags[0] == 0
				&& flags[1] == 0)))
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_str_write(va_list vl, char *flags, int width, int prec)
{
	char	*str;
	int		charno;

	str = va_arg(vl, char *);
	if (!str && (flags[0] + flags[1] == 0 || prec > 5))
		str = "(null)";
	else if (!str)
		return (0);
	charno = 0;
	if (flags[7] == '*')
		width = va_arg(vl, int);
	if (flags[0] == '*')
		prec = va_arg(vl, int);
	if (prec < (int)ft_strlen(str) && flags[0] + flags[1] != 0)
		width -= prec;
	else
		width -= ft_strlen(str);
	while (flags[6] == 0 && width-- > 0)
		charno += write(1, " ", 1);
	charno += ft_putstr_printf(str, prec, flags);
	while (flags[6] != 0 && width-- > 0)
		charno += write(1, " ", 1);
	return (charno);
}
