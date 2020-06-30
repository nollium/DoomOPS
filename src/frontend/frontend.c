/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:42:17 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/30 21:48:29 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "frontend.h"

int		create_rgb(unsigned char r, unsigned char g,
					unsigned char b)
{
	return (r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x <= 0 || x >= data->width || y <= 0 || y >= data->height
	|| color == TRANS_COLOR)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}
