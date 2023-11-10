/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 09:46:31 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 10:52:47 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(va_list ptr)
{
	char	*str;
	int		len;

	len = 0;
	str = va_arg(ptr, char *);
	if (str == NULL)
	{
		ft_putstr("(null)", 1);
		len = 6;
	}
	else
		len = ft_putstr(str, 1);
	return (len);
}

int	print_char(va_list ptr)
{
	int	val;

	val = va_arg(ptr, int);
	write(1, &val, 1);
	return (1);
}
