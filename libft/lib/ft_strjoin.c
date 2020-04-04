/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:31:37 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/16 12:53:41 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libftprintf.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	char	*dst;
	size_t	s1_len;
	size_t	s2_len;
	size_t	max_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	max_len = s1_len + s2_len;
	if (!max_len)
		return (ft_strdup(""));
	if (!s1_len)
		return (ft_strdup(s2));
	if (!s2_len)
		return (ft_strdup(s1));
	if (!(dst = malloc(sizeof(char) * (max_len + 1))))
		return (NULL);
	ft_strlcpy(dst, s1, s1_len + 1);
	ft_strlcat(dst, s2, max_len + 1);
	return (dst);
}
