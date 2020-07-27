/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singletons.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 01:09:32 by user42            #+#    #+#             */
/*   Updated: 2020/07/27 13:02:27 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

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
