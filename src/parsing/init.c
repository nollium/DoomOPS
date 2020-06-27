/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/27 18:03:42 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void		init_img(void *mlx, int width, int height, t_data *img)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img,
	&(img->bits_per_pixel), &(img->line_length),
								 &(img->endian));
	img->width = width;
	img->height = height;
}

int			init_cam(t_camera *cam, t_spawn *spawn)
{
	static t_camera	cam_switcher[] = {
		(t_camera){0.0, 0.0, -1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, 0.66}},
		(t_camera){0.0, 0.0, 1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, -0.66}},
		(t_camera){0.0, 0.0, 0.0, -1.0, SPEED, TURN_SPEED,
		(t_plane){-0.66, 0.0}},
		(t_camera){0.0, 0.0, 0.0, 1.0, SPEED, TURN_SPEED,
		(t_plane){0.66, 0.0}},};
	int				i;

	i = 0;
	while (SPAWN_CHARS[i] && SPAWN_CHARS[i] != spawn->dir)
		i++;
	if (SPAWN_CHARS[i])
	{
		*cam = cam_switcher[i];
		cam->x = spawn->x;
		cam->y = spawn->y;
		return (SUCCESS_CODE);
	}
	else
		return (MAP_ERROR);	
}

int			init_vars(char *path, t_vars *vars)
{
	register int 	i;
	static char		*errors[] = {"NO ERROR", "UNKNOWN ERROR",
								"FILE INVALID ERROR", "MAP ERROR",
								"WRONG FILE EXTENSION", "NULL ERROR",
								"MALLOC ERROR",
								"CONFIG ERROR", "RESOLUTION_ERROR",
								"COLOR ERROR"};
	int				error;

	i = -1;
	while (++i < K_BUFF_SIZE)
		(vars->keys)[i] = (t_keys){-1, 0};
	if ((error = load_cub(path, vars)) != SUCCESS_CODE)
	{
		ft_putendl_fd(errors[-error], 2);
		exit (1);
	}
	init_cam(&(vars->cam), &(vars->spawn));
	vars->z_buffer = malloc(sizeof(double) * vars->game_screen.width);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, vars->game_screen.width, vars->game_screen.height, "cub3D");
	init_img(vars->mlx, vars->game_screen.width, vars->game_screen.height, vars->img2);
	init_img(vars->mlx, vars->game_screen.width, vars->game_screen.height, vars->img2 + 1);
	char **text_paths = vars->text_paths;
	i = -1;
	while (text_paths[++i]);
	vars->text = malloc(sizeof(t_texture) * (i + 1));
	i = -1;
	if (!(vars->text && vars->sprites))
		ft_putendl_fd("MALLOC ERROR", 1);
	while (text_paths[++i])	
		if (load_texture(vars->text + i, text_paths[i], vars->mlx) == -1)
			return (TEXTURE_ERROR);
	vars->text[i] = (t_texture) {0};
	return (SUCCESS_CODE);
}