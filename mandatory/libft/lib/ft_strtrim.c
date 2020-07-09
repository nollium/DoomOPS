/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:05:51 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/18 15:40:07 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"
#include <stddef.h>
#include <stdlib.h>

static int	is_in_set(char	const *s1, char const *set)
{
	while (set)
		if (ft_strrchr(s1, *set++))
			return (1);
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	size_t	min;
	size_t	max;

	min = 0;
	if (!s1)
		return (NULL);
	if (!set || !set[0] || !s1[0] || !is_in_set(s1, set))
		return (ft_strdup(s1));
	while (s1[min] != '\0' && ft_strchr(set, s1[min]))
		min++;
	max = ft_strlen(s1);
	if (max == 0 || min == max)
		return (ft_strdup(""));
	if (!set || !set[0] || !is_in_set(s1, set))
		return (ft_strdup(s1));
	while (ft_strchr(set, s1[max]))
		max--;
	if (max <= min)
		return (ft_strdup(""));
	return (ft_substr(s1, min, max - min + 1));
}
