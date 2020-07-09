/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 10:07:47 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/06 07:21:06 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned	char		*d;
	const	unsigned char	*s;

	d = dst;
	s = src;
	if (!dst && !src)
		return (0);
	if (d < s)
		while (len--)
			*d++ = *s++;
	else
		while (len--)
			*(d + len) = *(s + len);
	return (dst);
}
