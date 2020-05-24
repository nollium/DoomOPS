/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/24 20:09:15 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static	void		mikasa()
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

static void		generate_texture(t_texture *texture)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	texture->width = 64;
	texture->height = 64;
	texture->array = malloc(sizeof(int) * texture->width * texture->height);
	while(++x < texture->width)
	{
		y = -1;
		while (++y < texture->height)
			texture->array[texture->width * y + x] = 0X00FF0000 * 192 * (x % 16 && y % 16);//0xFF *  y * 256 / TEX_HEIGHT;
	}
}

void		init_vars(int width, int height, t_vars *vars)
{
	int 	i;

	//mikasa();
	i = -1;
	while (++i < K_BUFF_SIZE)
		(vars->keys)[i] = (t_keys){-1, 0};
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, width, height, "cub3D");
	vars->img2.img = mlx_new_image(vars->mlx, width, height);
	vars->img2.addr = mlx_get_data_addr(vars->img2.img, &(vars->img2.bits_per_pixel), &(vars->img2).line_length,
								 &(vars->img2).endian);
	vars->img2.width = width;
	vars->img2.height = height;
	vars->cam = (t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED, (t_plane){0.0, 0.66}};
	vars->map = (t_map)
	{
		0,0,
		{
			{'1','1','1','1','1','1','1'},
			{'1','0','0','1','0','0','1','1','1','1'},
			{'1','0','0','0','1','0','0','0','0','1'},
			{'1','0','0','0','0','0','1','1','1','1'},
			{'1','0','0','0','0','0','1'},
			{'1','1','1','1','1','1','1'}
		}
	};
	generate_texture(&(vars->text));
}