/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 18:37:39 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/17 16:36:54 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	int		res;
	size_t	i;

	i = 0;
	res = 0;
	if (n == 0)
		return (0);
	while (i < n && res == 0)
	{
		if (s1[i] == 0 && s2[i] == 0)
			return (0);
		res = (unsigned char)s1[i] - (unsigned char)s2[i];
		i++;
	}
	return (res);
}
