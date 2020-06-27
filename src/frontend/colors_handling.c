/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:58:15 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 18:30:50 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frontend.h"
#include <stdint.h>



int add_shade(double shade, int color)
{
	unsigned char rgb[4];

	if (0 > shade || color == 0x1)
		return (color);
	if (shade >= 1)
		return (0);
	*(int *)rgb = color;
	rgb[0] *= (1.0 - shade);
	rgb[1] *= (1.0 - shade);
	rgb[2] *= (1.0 - shade);
	return (*(int *)rgb);
}
