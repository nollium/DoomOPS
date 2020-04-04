/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:04:19 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/14 16:20:59 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*dst;

	i = -1;
	if (!s)
		return (NULL);
	if (!(dst = ft_strdup(s)) || !s)
		return (NULL);
	if (!f)
		return (dst);
	while (dst[++i])
		dst[i] = (*f)((unsigned int)i, dst[i]);
	return (dst);
}
