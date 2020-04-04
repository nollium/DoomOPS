/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 16:37:22 by smaccary          #+#    #+#             */
/*   Updated: 2019/12/08 19:34:45 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

char	*ft_strndup(const char *s1, long long n)
{
	char	*str;
	size_t	i;

	if (n <= 0)
		return (ft_strdup(""));
	if (!(str = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (s1[i] && (long long)i < n)
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
