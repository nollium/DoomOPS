/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 07:23:32 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/17 16:35:12 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char *str;

	str = (char *)s;
	while (n--)
		if (*str == (char)c)
			return ((void *)str);
		else
			str++;
	return (0);
}
