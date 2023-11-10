/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_digits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 10:05:30 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 10:26:25 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	check_length(int n)
{
	int	count;

	count = 0;
	if (n == -2147483648)
		return (11);
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count + 1);
}

static	int	unsigned_check_length(unsigned int n)
{
	int	count;

	count = 0;
	while (n >= 10)
	{
		n = n / 10;
		count++;
	}
	return (count + 1);
}

static	void	putnbr(int n, int fd)
{
	char	digit;

	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = n * (-1);
		write(fd, "-", 1);
	}
	if (n > 9)
	{
		putnbr(n / 10, fd);
		putnbr(n % 10, fd);
	}
	if (n < 10)
	{
		digit = n + 48;
		write(fd, &digit, 1);
	}
}

static	void	unsigned_putnbr(unsigned int n, int fd)
{
	char	digit;

	if (n > 9)
	{
		unsigned_putnbr(n / 10, fd);
		unsigned_putnbr(n % 10, fd);
	}
	if (n < 10)
	{
		digit = n + 48;
		write(fd, &digit, 1);
	}
}

int	print_digits(va_list ptr, char c)
{
	int				len;
	unsigned int	sign;

	len = 0;
	if (c == 'd' || c == 'i')
	{
		sign = va_arg(ptr, int);
		putnbr(sign, 1);
		len = check_length(sign);
	}
	else if (c == 'u')
	{
		sign = va_arg(ptr, unsigned int);
		unsigned_putnbr(sign, 1);
		len = unsigned_check_length(sign);
	}
	return (len);
}
