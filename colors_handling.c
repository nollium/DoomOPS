/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 12:58:15 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/17 14:21:10 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
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

/* broken LSD mode
int add_shade(double shade, int color)
{
	unsigned char rgb[3];

	if (0 > shade || color == 0x1)
		return (color);
	if (shade > 1)
		shade = 1;
		/*
	*(int *)rgb = color;
	
	rgb[0] = rgb[0] - shade * rgb[0];
	rgb[1] = rgb[1] - shade * rgb[1];
	rgb[2] = rgb[2] - shade * rgb[2];
	
	return (*(int *)rgb);
	return (shade * color);
}*/

/*
// weird transparency stuff, works for water / fog effect
int add_shade(double dist, int color)
{
	int i;
	int trgb[4];

	if (0 > dist || dist > 1)
	{
		dist = (dist < 0) ? 0 : 1;
		ft_putstr_fd("\e[1;35m Warning : \e[0m add_shade should only use a shade between 0 and 1.\n", 1);
	}
	trgb[0] = color & 0xFF;
	trgb[1] = (color >> 8) & 0xFF;
	trgb[2] = (color >> 16) & 0xFF;
	trgb[3] = (color >> 24) & 0xFF;
	i = -1;
	while (++i < 3)
		trgb[i] = trgb[i] - dist * trgb[i];
  	return(trgb[3] << 24 | trgb[2] << 16 | trgb[1] << 8 | trgb[0]);
}
*/