/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/01 19:09:13 by smaccary         ###   ########.fr       */
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
		(vars->keys)[i] = (t_keys){-1, 0};
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, width, height, "Hello world!");
	vars->img2.img = mlx_new_image(vars->mlx, width, height);
	vars->img2.addr = mlx_get_data_addr(vars->img2.img, &(vars->img2.bits_per_pixel), &(vars->img2).line_length,
								 &(vars->img2).endian);
	vars->cam = (t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED, (t_plane){0.0, 0.66}};
	vars->map = (t_map){0,0,{
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},\
	{'1','1','1','1','1','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','1','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','1','0','0','0','1','1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','1','0','0','0','1','1','2','2','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},\
	{'1','1','1','1','1','1','1','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','1','1','1','1','1','1','0','0','0','2','0','0','0','0','3','0','0','0','3','0','0','0','1'},\
	{'1','0','0','0','0','0','2','0','0','0','2','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','2','2','0','2','2','0','0','0','0','3','0','3','0','3','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','0','0','0','0','5','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','0','4','0','0','0','0','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','0','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','4','4','4','4','4','4','4','4','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'},\
	{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}}};
}