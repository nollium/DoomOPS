/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/04/18 11:57:17 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		mikasa()
{
	char    *line;
	int     fd;
	
	fd = open("mikasa", O_RDONLY);
	while (get_next_line(fd, &line) == 1)
	{
		ft_printf("\e[31m%s\e[0m\n", line);
		free(line);
	}
	free(line);
	close(fd);
}

void		init_vars(int width, int height, t_vars *vars)
{
	int i;

	//mikasa();
	i = -1;
	while (++i < K_BUFF_SIZE)
	{
		(vars->keys)[i].keycode = -1;
		(vars->keys)[i].time = 0;
	}
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, width, height, "Hello world!");
	vars->img2.img = mlx_new_image(vars->mlx, width, height);
	vars->img2.addr = mlx_get_data_addr(vars->img2.img, &(vars->img2.bits_per_pixel), &(vars->img2).line_length,
								 &(vars->img2).endian);
    vars->cam.x = SPAWN_X;
    vars->cam.y = SPAWN_Y;
    vars->cam.dir_x = -1;
    vars->cam.dir_y = 0;
    vars->cam.plane.x = 0;
    vars->cam.plane.y = 0.66;
}