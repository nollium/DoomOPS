/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 08:30:07 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/24 15:39:28 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dstlen;

	dstlen = ft_strnlen(dst, size);
	if (size > dstlen)
		return (dstlen + ft_strlcpy(dst + dstlen, src, size - dstlen));
	return (dstlen + ft_strlen(src));
}
