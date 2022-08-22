/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uint_write.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:07:56 by obibby            #+#    #+#             */
/*   Updated: 2022/07/01 22:20:28 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	un_charcount(unsigned int x)
{
	int	i;

	i = 0;
	if (x == 0)
		return (1);
	while (x != 0)
	{
		x /= 10;
		i++;
	}
	return (i);
}

char	*ft_unitoa(unsigned int n)
{
	int			i;
	char		*str;

	i = un_charcount(n);
	str = malloc(sizeof(char) * (i + 1));
	if (str == NULL)
		return (NULL);
	str[i] = '\0';
	while (i-- > 0)
	{
		str[i] = (n % 10) + '0';
		n /= 10;
	}
	return (str);
}

int	ft_uint_write(va_list vl, char *flags, int width, int prec)
{
	unsigned int	n;
	char			*str;
	int				charno;

	n = va_arg(vl, int);
	str = ft_unitoa(n);
	charno = 0;
	if (flags[7] == '*')
		width = va_arg(vl, int);
	if (flags[0] == '*')
		prec = va_arg(vl, int);
	if (prec > (int)ft_strlen(str))
		width -= prec;
	else if (str[0] != '0' || prec != 0 || flags[0] + flags[1] == 0)
		width -= (int)ft_strlen(str);
	charno += print_int(str, flags, width, prec);
	free(str);
	return (charno);
}
