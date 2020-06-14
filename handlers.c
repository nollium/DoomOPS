/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:45:37 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/14 00:30:28 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int				free_garbage(t_vars *vars)
{
	mlx_do_key_autorepeaton(vars->mlx);
    mlx_destroy_window(vars->mlx, vars->win);
	exit(0);	
}

int             key_handler(int keycode, t_vars *vars)
{
	int i;

	i = -1;
	if (DEBUG_MODE)
		ft_printf("Key pressed : %d\n", keycode);
	if (keycode == 65307)
		free_garbage(vars);
	if (keycode == 178)
	{
		if (DEBUG_MODE)
			ft_printf("Pressed keys : ");
		while (++i < K_BUFF_SIZE)
			if (DEBUG_MODE)
				ft_printf((((vars->keys)[i]).keycode != -1) ? "%d, " : "", (vars->keys)[i].keycode);
		write(1, "\n", 1);
	}
	i = -1;
	while (i < K_BUFF_SIZE && (((vars->keys)[i]).keycode != -1))
		i++;
	if (((vars->keys)[i]).keycode != -1)
		return (0);
	((vars->keys)[i]).keycode = keycode;
	((vars->keys)[i]).time = time(NULL);
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
		if (DEBUG_MODE)
			ft_printf("x0 %d y0 %d x1 %d y1 %d\n", x_0, y_0, x, y);
		my_line_put(vars->img, x_0, y_0, x, y, 0x00FFFFFF);
		x_0 = -1;
		y_0 = -1;
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img->img, 0, 0);
	//	vars->redraw = 1;
	}
	if (DEBUG_MODE)
		ft_printf("Mouse %d at : x%d\t\ty%d\n", button, x, y);
	return (0);
}

int			move_handler(void)
{
	if (DEBUG_MODE)
		ft_printf("Moving\n");
	return (0);
}

int			resize_handler(void)
{
	if (DEBUG_MODE)
		ft_printf("Resizing window\n");
	return (0);
}

int			enter_handler(void)
{
	if (DEBUG_MODE)
		ft_printf("Entering window\n");
	return (0);	
}

int			leave_handler(void)
{
	if (DEBUG_MODE)
		ft_printf("Leaving window\n");
	return (0);
}

int			release_handler(int keycode, t_vars *vars)
{
	static int		count = 0;
	int				i;
	time_t			elapsed;

	i = -1;
	while (++i < K_BUFF_SIZE)
	{
		if ((vars->keys[i]).keycode == keycode)
		{
			if (i >= K_BUFF_SIZE)
				return (0);
			elapsed = (time(NULL) - ((vars->keys)[i]).time);
			if (elapsed > 10000 || elapsed < 0)
				if (DEBUG_MODE)
					ft_printf("wtf bruce \n");
			if (DEBUG_MODE)
				ft_printf("index:%d\nKey %d released %d th time for %ld s\n", i, keycode, ++count, elapsed);
			((vars->keys)[i]).keycode = -1;
			((vars->keys)[i]).time = 0;
		}
	}
	return (0);
}

t_keys	*key_chr(t_keys *arr, int keycode, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		if (arr[i].keycode == keycode)
			return (arr + i);
	return (NULL);
}

