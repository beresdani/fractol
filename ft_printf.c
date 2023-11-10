/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:15:34 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 12:08:59 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"
#include <unistd.h>

static	int	check_format(const char *s, va_list ptr, char c, int i)
{
	int		len;
	int		*count;

	len = 0;
	count = &len;
	if (c == 'd' || c == 'i' || c == 'u')
		len = print_digits(ptr, c);
	else if (c == 'c')
		len = print_char(ptr);
	else if (c == 'p')
		len = print_pointer(ptr, count);
	else if (c == 's')
		len = print_string(ptr);
	else if (c == 'x' || c == 'X')
	{
		ft_change_base(va_arg(ptr, unsigned int), 16, count, c);
		len = *count + 1;
	}
	else
	{
		write(1, &s[i - 1], 1);
		write(1, &s[i], 1);
		len = 2;
	}
	return (len);
}

static	int	is_percent(const char *s, int i)
{
	int	is_percent;

	is_percent = 0;
	if (s[i] == '%' && s[i + 1] == '%')
		is_percent = 1;
	return (is_percent);
}

static	int	handle_is_percent(const char *s, int i)
{
	i++;
	write(1, &s[i], 1);
	return (i);
}

int	print_chars(const char *s, va_list ptr)
{
	int		i;
	int		len2;

	i = -1;
	len2 = 0;
	while (s[++i])
	{
		if (s[i] == '%' && s[i + 1] == 0)
			return (-1);
		else if (is_percent(s, i) == 1)
		{
			i = handle_is_percent(s, i);
			len2--;
		}
		else if (s[i] == '%')
		{
			i++;
			len2 = len2 - 2 + check_format(s, ptr, s[i], i);
		}
		else
			write(1, &s[i], 1);
	}
	if (is_percent(s, i) == 1)
		i--;
	return (i + len2);
}

int	ft_printf(const char *s, ...)
{
	va_list	ptr;
	int		len;

	if (!s)
		return (-1);
	va_start(ptr, s);
	len = print_chars(s, ptr);
	va_end(ptr);
	return (len);
}


#include <stdio.h>

int main(void)
{
	int	result1;
	int	result2;

	result1 = ft_printf("b% r Y%");
	printf("\n");
	result2 = printf("b% r  Y%");
	printf("\n");
	printf("%d\n%d\n", result1, result2);
	return (0);
}

