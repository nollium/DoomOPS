/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strreplace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libftprintf.h"

/*
**  Replaces all occurences of old in src by new
**  Returns the number of replaced chars
*/

int	ft_strreplace(char *src, char old, char new)
{
	size_t count;
	size_t i;

	count = 0;
	i = -1;
	if (!src)
		return (-1);
	while (src[++i])
		if (src[i] == old)
		{
			src[i] = new;
			count++;
		}
	return ((int)count);
}

/*
**  Replaces all occurences of charset's chars in src by new
**  Returns the number of replaced chars
*/

int	ft_replace_charset(char *src, char *charset, char new)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	if (!src || !charset)
		return (-1);
	while (charset[++i])
		count += ft_strreplace(src, charset[i], new);
	return ((int)count);
}
