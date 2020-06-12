/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/12 22:01:49 by smaccary         ###   ########.fr       */
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

int	load_texture(t_texture *text, char *path, void *mlx)
{
	t_data data;

	if (load_xpm(&data, path, mlx) == -1)
		return (-1);
	img_to_text(&data, text);
	mlx_destroy_image(mlx, data.img);
	return (0);
}

void		init_img(void *mlx, int width, int height, t_data *img)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img,
	&(img->bits_per_pixel), &(img->line_length),
								 &(img->endian));
	img->width = width;
	img->height = height;
}

void		init_vars(int width, int height, t_vars *vars)
{
	register int 	i;

	//mikasa();
	i = -1;
	while (++i < K_BUFF_SIZE)
		(vars->keys)[i] = (t_keys){-1, 0};
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, width, height, "cub3D");
	init_img(vars->mlx, width, height, vars->img2);
	init_img(vars->mlx, width, height, vars->img2 + 1);
	vars->cam = (t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED,
	(t_plane){0.0, 0.66}};
	vars->map = (t_map)
	{
		0,0,
		{
			{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'},
			{'1','1','0','0','0','1','1','1','0','0','0','0','0','1','1','1'},
			{'1','0','0','0','0','0','1','1','0','0','0','0','0','1','1','1'},
			{'1','0','0','0','0','0','0','0','0','0','0','0','0','0','0','1'}, //10,4
			{'1','0','0','1','0','0','0','0','0','0','0','0','0','0','0','1'},
			{'1','0','0','0','0','0','1','1','0','0','0','0','0','1','1','1'},
			{'1','0','0','0','0','0','1','1','0','0','0','0','0','1','1','1'},
			{'1','1','1','1','1','1','1','1','1','1','1','1','1','1','1','1'}
		}
	};
	

	char *text_paths[] = {	"pics/NO.xpm",
							"pics/SO.xpm",
							"pics/EA.xpm",
							"pics/WE.xpm",
							"pics/small_shrek.xpm",
							"pics/128x128.xpm",
							"pics/small_shrek.xpm",
							"pics/hud.xpm",
							0};

	i = -1;
	while (text_paths[++i]);
	vars->text = malloc(sizeof(t_texture) * (i + 1));
	vars->sprites = malloc(sizeof(t_sprite) * 3);
	i = -1;
	if (!(vars->text && vars->sprites))
		ft_putendl_fd("MALLOC ERROR", 1);
	while (text_paths[++i])	
		if (load_texture(vars->text + i, text_paths[i], vars->mlx) == -1)
			ft_printf("\e[31mTEXTURE \"%s\" ERROR\e[31m\n", text_paths[i]);
	vars->text[i] = (t_texture) {0};
	

	vars->sprites[0] = (t_sprite){4.0, 10.0, 0, 5};

	vars->sprites[1] = (t_sprite){4.2, 2.3, 0, 6};
	vars->sprites[2] = (t_sprite){4.0, 13.0, 0, 4};
	vars->num_sprites = 4 - 4 + 3;
}