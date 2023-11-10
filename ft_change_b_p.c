/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_b_p.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 11:40:06 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 10:29:01 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_change_b_p(unsigned long long n, unsigned int base, int *count)
{
	char	c;
	int		k;

	k = *count;
	while (n >= base)
	{
		k++;
		*count = k;
		ft_change_b_p(n / base, base, count);
		n = n % base;
	}
	if (n < 10)
		c = n + 48;
	else
	{
		c = n + 87;
	}
	write(1, &c, 1);
}
/*
int main(void)
{
    int n = 793875;
    int base = 16;

    ft_change_base(n, base);
    return (0); 
}*/