/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:42:17 by smaccary          #+#    #+#             */
/*   Updated: 2020/04/16 12:39:37 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		create_trgb(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	if (x <= 0 || x >= WINDOW_WIDTH || y <= 0 || y >= WINDOW_HEIGHT)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 			my_line_put(t_data *data, int x0, int y0, int x1, int y1, int color)
{ 
	int dx = abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = abs(y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = (dx > dy ? dx : -dy) / 2, e2;
/*
	dx = abs(x1 - x0);
	sx = x0 < x1 ? 1 : -1;
	dy = abs(y1 - y0);
	sy = y0 < y1 ? 1 : -1;
	*/
	while(1)
	{
    	my_mlx_pixel_put(data, x0, y0, color);
    	if (x0==x1 && y0==y1) break;
    	e2 = err;
    	if (e2 >-dx) { err -= dy; x0 += sx; }
    	if (e2 < dy) { err += dx; y0 += sy; }
  	}
}

void			drawRectangle(t_data *data, int top_left[2], int bot_right[2])
{
	int i;

	i = top_left[0];
	while (i <= bot_right[0])
	{
		my_mlx_pixel_put(data, i, top_left[1], 0x00FFFFFF);
		my_mlx_pixel_put(data, i, bot_right[1], 0x00FFFFFF);
		i++;
	}
	i = top_left[1];
	while (i >= bot_right[1])
	{
		my_mlx_pixel_put(data, top_left[0], i, 0x00FFFFFF);
		my_mlx_pixel_put(data, bot_right[0], i, 0x00FFFFFF);
		i--;
	}
}
void			drawcircle(t_data *data, int x0, int y0, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
		my_mlx_pixel_put(data, x0 + x, y0 + y, color);
		my_mlx_pixel_put(data, x0 + y, y0 + x, color);
		my_mlx_pixel_put(data, x0 - y, y0 + x, color);
		my_mlx_pixel_put(data, x0 - x, y0 + y, color);
		my_mlx_pixel_put(data, x0 - x, y0 - y, color);
		my_mlx_pixel_put(data, x0 - y, y0 - x, color);
		my_mlx_pixel_put(data, x0 + y, y0 - x, color);
		my_mlx_pixel_put(data, x0 + x, y0 - y, color);
	
		if (err <= 0)
		{
			y += 1;
			err += 2*y + 1;
		}
	
		if (err > 0)
		{
			x -= 1;
			err -= 2*x + 1;
		}
    }
}

void			drawhalfcircle(t_data *data, int x0, int y0, int radius, int color)
{
    int x = radius;
    int y = 0;
    int err = 0;
 
    while (x >= y)
    {
		my_mlx_pixel_put(data, x0 - x, y0 - y, color);
		my_mlx_pixel_put(data, x0 - y, y0 - x, color);
		my_mlx_pixel_put(data, x0 + y, y0 - x, color);
		my_mlx_pixel_put(data, x0 + x, y0 - y, color);
	
		if (err <= 0)
		{
			y += 1;
			err += 2*y + 1;
		}
	
		if (err > 0)
		{
			x -= 1;
			err -= 2*x + 1;
		}
    }
}

void			draw_gradient(t_data *data)
{
	int x = 0;
	int y = 0;
	double i = 0;

	while (y < WINDOW_HEIGHT)
	{
		i += 0.05;
		x = 0;
		while (x < WINDOW_WIDTH)
			{
				my_mlx_pixel_put(data, x, y, create_trgb(255, sin(0.3 * i) * 127 + 128, sin(0.3 * i + 2.0) * 127 + 128, sin(0.3 * i + 4.0) * 127 + 128));
				x++;
			}
		
		y++;
	}
}

void			draw_rainbow(t_data *data)
{
	int x = 1000;
	int y = 900;
	int r = 500; 
	int color = 0xFFFFFFFF;
	double i = 0;

	while (++r < 900)
	{
		drawhalfcircle(data, x, y, r, create_trgb(255, sin(0.17 * i) * 127 + 128, sin(0.17 * i + 2.0) * 127 + 128, sin(0.17 * i + 4.0) * 127 + 128));
		i += 0.0965;
	}
}