/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 13:47:28 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/24 19:06:32 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t srclen;

	srclen = ft_strlen(src);
	if (srclen + 1 < dstsize)
		ft_memcpy(dest, src, srclen + 1);
	else if (dstsize != 0)
	{
		ft_memcpy(dest, src, dstsize - 1);
		dest[dstsize - 1] = '\0';
	}
	return (srclen);
}
