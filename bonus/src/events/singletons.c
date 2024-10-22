/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 18:30:19 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 18:30:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"
#include "garbage_collection.h"

int		leave(t_vars *vars)
{
	free_vars(vars);
	exit(0);
	return (0);
}

void	check_pitch(double *ptr)
{
	if (ptr)
	{
		if (*ptr < MIN_PITCH)
			*ptr = MIN_PITCH;
		if (*ptr > MAX_PITCH)
			*ptr = MAX_PITCH;
	}
}
