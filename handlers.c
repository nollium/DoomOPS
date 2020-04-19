/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/11 13:45:37 by smaccary          #+#    #+#             */
/*   Updated: 2020/04/19 16:26:30 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int             key_handler(int keycode, t_vars *vars)
{
	int i;

	i = -1;
	ft_printf("Key pressed : %d\n", keycode);
	if (keycode == 65307)
	{
		mlx_do_key_autorepeaton(vars->mlx);
    	mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	if (keycode == 178)
	{
		ft_printf("Pressed keys : ");
		while (++i < K_BUFF_SIZE)
			ft_printf((((vars->keys)[i]).keycode != -1) ? "%d, " : "", (vars->keys)[i].keycode);
		write(1, "\n", 1);
	}
	i = -1;
	while (i < K_BUFF_SIZE && ((vars->keys)[i]).keycode != -1)
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
		ft_printf("x0 %d y0 %d x1 %d y1 %d\n", x_0, y_0, x, y);
		my_line_put(vars->img, x_0, y_0, x, y, 0x00FFFFFF);
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

int			release_handler(int keycode, t_vars *vars)
{
	static int		count = 0;
	int				i;
	int				tmp;
	time_t			elapsed;

	i = 0;
	while (i < K_BUFF_SIZE && ((vars->keys)[i]).keycode != keycode)
		i++;
	if (i >= K_BUFF_SIZE)
		return (0);
	elapsed = (time(NULL) - ((vars->keys)[i]).time);
	if (elapsed > 10000 || elapsed < 0)
		ft_printf("wtf bruce \n");
	ft_printf("index:%d\nKey %d released %d th time for %ld s\n", i, keycode, ++count, elapsed);
	((vars->keys)[i]).keycode = -1;
	((vars->keys)[i]).time = 0;
	return (0);
}

static t_keys	*key_chr(t_keys *arr, int keycode, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		if (arr[i].keycode == keycode)
			return (arr + i);
	return (NULL);
}

int			loop_handler(t_vars *vars)
{
	int worldMap[MAP_WIDTH][MAP_HEIGHT] =
	{
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int		redraw;
	clock_t	t0;

	redraw = 0;
	if (key_chr(vars->keys, FORWARD_KEY, K_BUFF_SIZE))
	{
		redraw = 1;
		if (worldMap[(int)(vars->cam.x + vars->cam.dir_x * SPEED)][(int)(vars->cam.y)] == 0)
			vars->cam.x += vars->cam.dir_x * SPEED;
    	if (worldMap[(int)(vars->cam.x)][(int)(vars->cam.y + vars->cam.dir_y * SPEED)] == 0)
			vars->cam.y += vars->cam.dir_y * SPEED;

	}
	if (key_chr(vars->keys, BACKWARD_KEY, K_BUFF_SIZE))
	{
		redraw = 1;
		if (worldMap[(int)(vars->cam.x - vars->cam.dir_x * SPEED)][(int)(vars->cam.y)] == 0)
			vars->cam.x -= vars->cam.dir_x * SPEED;
    	if (worldMap[(int)(vars->cam.x)][(int)(vars->cam.y - vars->cam.dir_y * SPEED)] == 0)
			vars->cam.y -= vars->cam.dir_y * SPEED;
	
	}
	if (key_chr(vars->keys, RIGHT_KEY, K_BUFF_SIZE))
	{
	//	ft_printf("RIGHT\n");
		redraw = 1;
    	double oldDirX = vars->cam.dir_x;
    	vars->cam.dir_x = vars->cam.dir_x * cos(-TURN_SPEED) - vars->cam.dir_y * sin(-TURN_SPEED);
    	vars->cam.dir_y = oldDirX * sin(-TURN_SPEED) + vars->cam.dir_y * cos(-TURN_SPEED);
    	double oldPlaneX = vars->cam.plane.x;
    	vars->cam.plane.x = vars->cam.plane.x * cos(-TURN_SPEED) - vars->cam.plane.y * sin(-TURN_SPEED);
    	vars->cam.plane.y = oldPlaneX * sin(-TURN_SPEED) + vars->cam.plane.y * cos(-TURN_SPEED);
	}
	if (key_chr(vars->keys, LEFT_KEY, K_BUFF_SIZE))
	{
		redraw = 1;
    	double oldDirX = vars->cam.dir_x;
    	vars->cam.dir_x = vars->cam.dir_x * cos(TURN_SPEED) - vars->cam.dir_y * sin(TURN_SPEED);
    	vars->cam.dir_y = oldDirX * sin(TURN_SPEED) + vars->cam.dir_y * cos(TURN_SPEED);
    	double oldPlaneX = vars->cam.plane.x;
    	vars->cam.plane.x = vars->cam.plane.x * cos(TURN_SPEED) - vars->cam.plane.y * sin(TURN_SPEED);
    	vars->cam.plane.y = oldPlaneX * sin(TURN_SPEED) + vars->cam.plane.y * cos(TURN_SPEED);
	}
	if (redraw)
	{
		draw_scene(vars);
		mlx_put_image_to_window(vars->mlx, vars->win, (vars->img)->img, 0, 0);
		printf("DRAWING : x%f y%f\n", vars->cam.x, vars->cam.y);
		t0 = clock();
		while (clock() - t0 < CLOCKS_PER_SEC / 30);
	}	
	return (0);
}