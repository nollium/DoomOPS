/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frontend.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:42:17 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/22 16:54:34 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		rgb_to_trgb(unsigned char t, int rgb)
{
	create_trgb(t, (rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, (rgb) & 0xFF);
}

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
	int d[2];
	int s[2];
	int err;
	int e2;

	d[0] = abs(x1 - x0);
	s[0] = (x0 < x1) ? 1 : -1;
	d[1] = abs(y1 - y0);
	s[1] = (y0 < y1) ? 1 : -1;
	err = ((d[0] > d[1]) ? d[0] : -d[1]) / 2;
	while(!(x0==x1 && y0==y1))
	{
    	my_mlx_pixel_put(data, x0, y0, color);;
    	e2 = err;
    	if (e2 >-d[0])
		{
			err -= d[1];
			x0 += s[0];
		}
    	if (e2 < d[1])
		{
			err += d[0];
			y0 += s[1];
		}
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
				my_mlx_pixel_put(data, x, y, add_shade(0.5, create_trgb(255, sin(0.3 * i) * 127 + 128, sin(0.3 * i + 2.0) * 127 + 128, sin(0.3 * i + 4.0) * 127 + 128)));
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