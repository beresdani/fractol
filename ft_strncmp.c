/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dberes <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:08:04 by dberes            #+#    #+#             */
/*   Updated: 2023/09/19 11:15:15 by dberes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p1;
	unsigned char	*p2;

	i = 0;
	p1 = (unsigned char *)s1;
	p2 = (unsigned char *)s2;
	while (i < n && (p1[i] != '\0' || p2[i] != '\0'))
	{
		if (p1[i] < p2[i])
			return (-1);
		else if (p1[i] > p2[i])
			return (1);
		i++;
	}
	return (0);
}

/*
#include <stdio.h>

int main(void)
{
    char    *s1;
    char    *s2;

    s1 = "\200";
    s2 = "\0";
    printf("%d\n", ft_strncmp(s1, s2, 8));
    printf("%d\n", strncmp(s1, s2, 8));
    return (0);
}
*/
