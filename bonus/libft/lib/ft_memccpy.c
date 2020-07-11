/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 07:33:13 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/24 18:28:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libftprintf.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	int					flag;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	c = (unsigned char)c;
	flag = 0;
	if (ft_memchr(s, c, n))
	{
		n = (unsigned char *)ft_memchr(s, c, n) - s + 1;
		flag = 1;
	}
	while (n--)
		*d++ = *s++;
	return ((flag) ? d : 0);
}
