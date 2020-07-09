/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 07:12:12 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/10 19:46:58 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	if (!src && !dst)
		return (0);
	while (n--)
		*(char *)(dst + n) = *(char *)(src + n);
	return (dst);
}
