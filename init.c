/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/17 18:05:21 by smaccary         ###   ########.fr       */
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

int			init_cam(t_camera *cam, char spawn_direction)
{
	static t_camera	cam_switcher[] = {
		(t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, 0.66}},
		(t_camera){SPAWN_X, SPAWN_Y, 1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, -0.66}},
		(t_camera){SPAWN_X, SPAWN_Y, 0.0, -1.0, SPEED, TURN_SPEED,
		(t_plane){-0.66, 0.0}},
		(t_camera){SPAWN_X, SPAWN_Y, 0.0, 1.0, SPEED, TURN_SPEED,
		(t_plane){0.66, 0.0}},};
	char			*dir_str;
	int				i;
	dir_str = "SNEW";
	i = 0;
	while (dir_str[i] && dir_str[i] != spawn_direction)
		i++;
	if (dir_str[i])
	{
		*cam = cam_switcher[i];
		return (1);
	}
	else
		return (0);	
}

int		init_vars(char *path, t_vars *vars)
{
	register int 	i;
	static char		*errors[] = {"NO ERROR", "UNKNOWN ERROR",
								"FILE INVALID ERROR", "MAP ERROR",
								"WRONG FILE EXTENSION", "NULL ERROR",
								"MALLOC ERROR",
								"CONFIG ERROR", "RESOLUTION_ERROR",
								"COLOR ERROR"};
	int				error;

	//mikasa();
	i = -1;
	while (++i < K_BUFF_SIZE)
		(vars->keys)[i] = (t_keys){-1, 0};
	init_cam(&(vars->cam), SPAWN_DIR);
	if ((error = load_cub(path, vars)) != SUCCESS_CODE)
	{
		ft_putendl_fd(errors[-error], 2);
		free_garbage(vars);
		return (error);
	}
	vars->z_buffer = malloc(sizeof(double) * vars->game_screen.width);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->game_screen.width, vars->game_screen.height, "cub3D");
	init_img(vars->mlx, vars->game_screen.width, vars->game_screen.height, vars->img2);
	init_img(vars->mlx, vars->game_screen.width, vars->game_screen.height, vars->img2 + 1);
	/*char *text_paths[] = {	"pics/NO.xpm",
							"pics/SO.xpm",
							"pics/EA.xpm",
							"pics/WE.xpm",
							"pics/small_shrek.xpm",
							"pics/128x128.xpm",
							"pics/small_shrek.xpm",
							"pics/hud.xpm",
							0};*/

	char **text_paths = vars->text_paths;
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
	

	vars->sprites[0] = (t_sprite){8.0, 6.0, 0, 4};

	vars->sprites[1] = (t_sprite){10.2, 2.3, 0, 4};
	vars->sprites[2] = (t_sprite){4.0, 5.0, 0, 4};
	vars->num_sprites = 4 - 4 + 3;
	return (SUCCESS_CODE);
}