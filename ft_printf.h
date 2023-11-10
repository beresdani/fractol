/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <dberes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 15:01:07 by dberes            #+#    #+#             */
/*   Updated: 2023/09/28 10:26:29 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h> 
# include <string.h> 
# include <stdlib.h>
# include <limits.h>
# include <ctype.h>
# include <stdarg.h>

/*# include "libft/libft.h"*/

int		ft_printf(const char *s, ...);
void	ft_putchar_fd(char c, int fd);
int		ft_putstr(char *s, int fd);
void	ft_change_base(unsigned int n, unsigned int base, int *count, char c);
void	ft_change_b_p(unsigned long long n, unsigned int base, int *count);
int		print_string(va_list ptr);
int		print_pointer(va_list ptr, int *count);
int		print_digits(va_list ptr, char c);
int		print_char(va_list ptr);

#endif // FT_PRINTF_H