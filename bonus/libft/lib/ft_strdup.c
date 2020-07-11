/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 21:57:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/02/15 16:06:28 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libftprintf.h"

char	*ft_strndup(const char *s1, int n)
{
	char	*str;
	int		i;

	if (n <= 0)
		return (ft_strdup(""));
	if (!(str = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*str;
	int		i;

	if (!(str = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	str[i] = '\0';
	return (str);
}
