/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 16:49:02 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/24 17:48:48 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../libftprintf.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int i;
	int index_find;

	i = 0;
	if (needle[0] == '\0' ||
			(needle == haystack && ft_strlen(needle) <= len))
		return ((char *)haystack);
	while (haystack[i])
	{
		index_find = 0;
		if (haystack[i] == needle[0])
		{
			while (haystack[i + index_find] == needle[index_find] &&
				i + index_find < (int)len)
			{
				index_find++;
				if (needle[index_find] == '\0')
					return ((char *)&haystack[i]);
			}
		}
		i++;
	}
	return (0);
}
