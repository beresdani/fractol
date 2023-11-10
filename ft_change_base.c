/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 13:11:19 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 10:28:35 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_change_base(unsigned int n, unsigned int base, int *count, char c)
{
	char	ch;
	int		k;

	k = *count;
	while (n >= base)
	{
		k++;
		*count = k;
		ft_change_base(n / base, base, count, c);
		n = n % base;
	}
	if (n < 10)
		ch = n + 48;
	else if (c == 'x')
		ch = n + 87;
	else
		ch = n + 55;
	write(1, &ch, 1);
}
/*
int main(void)
{
    int n = 793875;
    int base = 16;

    ft_change_base(n, base);
    return (0); 
}*/