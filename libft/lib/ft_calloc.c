/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:49:26 by smaccary          #+#    #+#             */
/*   Updated: 2019/11/10 19:44:00 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../libftprintf.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t		total;
	void		*ptr;

	total = (count && size) ? count * size : 1;
	if (!(ptr = malloc(total)))
		return (NULL);
	ft_bzero(ptr, total);
	return (ptr);
}
