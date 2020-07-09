/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:32:37 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/24 18:15:56 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libftprintf.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;
	size_t	src_len;

	if (!s)
		return (NULL);
	src_len = ft_strlen(s);
	len = (src_len < len) ? src_len : len;
	if (len == 0 || start > src_len)
		return (ft_strdup(""));
	if (!(dst = malloc(sizeof(char) * len + 1)))
		return (NULL);
	ft_strlcpy(dst, (char *)(s + start), len + 1);
	return (dst);
}
