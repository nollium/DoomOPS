/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 08:15:16 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/17 16:35:36 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int			res;
	size_t		i;
	const char	*str1;
	const char	*str2;

	if (!n)
		return (0);
	str1 = s1;
	str2 = s2;
	i = 0;
	res = 0;
	while (i < n && res == 0)
	{
		res = (unsigned char)str1[i] - (unsigned char)str2[i];
		i++;
	}
	return (res);
}
