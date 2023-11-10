/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 09:56:34 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 10:26:23 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(va_list ptr, int *count)
{
	int					len;
	unsigned long long	num;

	num = va_arg(ptr, unsigned long long);
	if (!num)
	{
		len = ft_putstr("(nil)", 1);
		return (len);
	}
	else
	{
		len = ft_putstr("0x", 1);
		ft_change_b_p(num, 16, count);
		len = len + *count + 1;
	}
	return (len);
}
