/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:50:24 by slutymeme         #+#    #+#             */
/*   Updated: 2020/04/04 12:48:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libftprintf.h"
#include <mlx.h>
#include <fcntl.h>
#include "cub3D.h"
#include <math.h>
#include <X11/Xlib.h>
#


int		create_trgb(unsigned char a, unsigned char r, unsigned char g, unsigned char b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void 			my_line_put(t_data *data, int x0, int y0, int x1, int y1)
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
    	my_mlx_pixel_put(data, x0, y0, 0x00FFFFFF);
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

	while (y < 1080)
	{
		i += 0.05;
		x = 0;
		while (x < 1920)
			
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

int             key_handler(int keycode, t_vars *vars)
{
	int i;

	i = 0;
	ft_printf("Key pressed : %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_do_key_autorepeaton(vars->mlx);
    	mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	while (i < K_BUFF_SIZE - 1 && (vars->keys)[i].keycode != -1)
		i++;
	if ((vars->keys)[i].keycode != -1)
		return (0);
	(vars->keys)[i].keycode = keycode;
	(vars->keys)[i].time = time(NULL);
	return (0);
}

int			mouse_handler(int button, int x, int y, t_vars *vars)
{
	static int x_0 = -1;
	static int y_0 = -1;

	if (x_0 == -1 && y_0 == -1)
	{
		x_0 = x;
		y_0 = y;
	}
	else
	{
		ft_printf("x0 %d y0 %d x1 %d y1 %d\n", x_0, y_0, x, y);
		my_line_put(vars->img, x_0, y_0, x, y);
		x_0 = -1;
		y_0 = -1;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	}
	ft_printf("Mouse %d at : x%d\t\ty%d\n", button, x, y);
	return (0);
}

int			move_handler(void)
{
	ft_printf("Moving\n");
	return (0);
}

int			resize_handler(void)
{
	ft_printf("Resizing window\n");
	return (0);
}

int			enter_handler(void)
{
	ft_printf("Entering window\n");
	return (0);	
}

int			leave_handler(void)
{
	ft_printf("Leaving window\n");
	return (0);
}

void			wp_hook(void *win_ptr, int x_event,
						int x_mask, int (*funct)(), ...)
{
}

int			release_handler(int keycode, t_vars *vars)
{
	static int	count = 0;
	int			i;
	int			tmp;

	i = 0;
	while (i < K_BUFF_SIZE && ((vars->keys)[i]).keycode != keycode)
		if (((vars->keys)[i]).keycode == -1)
			return (0);
		else
			i++;
	if (i > K_BUFF_SIZE)
		return (0);
	ft_printf("Key %d released %d th time for %d s\n", keycode, ++count, time(NULL) - (vars->keys)[i].time);
	while (i + 1 < K_BUFF_SIZE && (vars->keys)[i + 1].keycode != -1)
	{
		(vars->keys)[i].keycode = (vars->keys)[i + 1].keycode;
		(vars->keys)[i].time = (vars->keys)[i + 1].time;
		i++;
	}
	return (0);
}

void		init_vars(t_vars *vars)
{
	int i;

	i = -1;
	while (++i < K_BUFF_SIZE)
		(vars->keys)[i].keycode = -1;
}

int main(void)
{
	char    *line;
	int     fd = open("mikasa", O_RDONLY);
	t_data  img;
	t_vars	vars;

	while (get_next_line(fd, &line) == 1)
	{
		ft_printf("\e[31m%s\e[0m\n", line);
		free(line);
	}
	free(line);
	close(fd);
	init_vars(&vars);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	vars.img = &img;
	//my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	//my_line_put(&img, 1, 1, 1000, 1000);
	//drawcircle(&img, 500, 500, 100, 0x00FFFFFF);
	//drawRectangle(&img, (int []){200, 200}, (int []){400, 0});
	//draw_gradient(&img);
	draw_rainbow(&img);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, KeyPress, KeyPressMask, key_handler, (void *) &vars);
	mlx_mouse_hook(vars.win, mouse_handler, &vars);
	mlx_hook(vars.win, ResizeRequest, 0, resize_handler, (void *) 0);
	mlx_hook(vars.win, EnterNotify, EnterWindowMask, enter_handler, NULL);
	mlx_hook(vars.win, LeaveNotify, LeaveWindowMask, leave_handler, NULL);
	//mlx_key_hook(vars.win, release_handler, NULL);
	mlx_hook(vars.win, KeyRelease, KeyReleaseMask, release_handler, &vars);
	mlx_do_key_autorepeatoff(vars.mlx);
	//mlx_hook(vars.win, MotionNotify, PointerMotionMask, move_handler, (void *) 0);
	mlx_loop(vars.mlx);
}