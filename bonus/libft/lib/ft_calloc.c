/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 17:49:26 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/11 21:10:25 by dirty            ###   ########.fr       */
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
