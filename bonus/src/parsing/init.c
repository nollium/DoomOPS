/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 13:31:27 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/16 19:48:06 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int			init_cam(t_camera *cam, t_spawn *spawn)
{
	t_camera		cam_switcher[4];
	int				i;

	i = 0;
	cam_switcher[0] = (t_camera){.dir_x = -1, .speed = SPEED,
	.turn_speed = TURN_SPEED, .plane = (t_plane){0, 0.66}};
	cam_switcher[1] = (t_camera){.dir_x = 1, .speed = SPEED,
	.turn_speed = TURN_SPEED, .plane = (t_plane){0, -0.66}};
	cam_switcher[2] = (t_camera){.dir_y = -1.0, .speed = SPEED,
	.turn_speed = TURN_SPEED, .plane = (t_plane){-0.66, 0.0}};
	cam_switcher[3] = (t_camera){.dir_y = 1.0, .speed = SPEED,
	.turn_speed = TURN_SPEED, .plane = (t_plane){0.66, 0.0}};
	while (SPAWN_CHARS[i] && SPAWN_CHARS[i] != spawn->dir)
		i++;
	if (SPAWN_CHARS[i])
	{
		*cam = cam_switcher[i];
		cam->x = spawn->x;
		cam->y = spawn->y;
		return (SUCCESS_CODE);
	}
	*cam = (t_camera){0};
	return (MAP_ERROR);
}

int			init_textures(t_vars *vars)
{
	int		i;
	char	**text_paths;

	text_paths = vars->text_paths;
	i = -1;
	if (load_texture(&(vars->gun), GUN_PATH, vars->mlx) != SUCCESS_CODE
		|| load_texture(&(vars->flash), FLASH_PATH, vars->mlx) != SUCCESS_CODE)
		return (TEXTURE_ERROR);
	while (text_paths[++i])
		;
	if (!(vars->text = malloc(sizeof(t_texture) * (i + 1))))
		return (MALLOC_ERROR);
	i = -1;
	while (text_paths[++i])
		if (load_texture(vars->text + i, text_paths[i], vars->mlx)
			!= SUCCESS_CODE)
		{
			vars->text[i] = (t_texture){0};
			free_textures(&(vars->text));
			return (TEXTURE_ERROR);
		}
	vars->text[i] = (t_texture) {0};
	return (SUCCESS_CODE);
}

static void	init_keys_buffer(t_keys *keys)
{
	int	i;

	i = -1;
	while (++i < K_BUFF_SIZE)
		keys[i] = (t_keys){-1, 0};
}

static int	init_2(t_vars *vars)
{
	int			error;
	int			i;
	static char *bar_path[] = {BAR_1_PATH, BAR_2_PATH, BAR_3_PATH,
								BAR_4_PATH, BAR_5_PATH, BAR_6_PATH};

	error = SUCCESS_CODE;
	if ((error = init_textures(vars)) != SUCCESS_CODE)
		return (error);
	(vars->gun).x = vars->game_screen.width / 2 - (vars->gun.width) / 2;
	(vars->gun).y = vars->game_screen.height - (vars->gun).height;
	(vars->flash).x = vars->game_screen.width / 2 - vars->flash.width / 2;
	(vars->flash).x += 60;
	(vars->flash).y = vars->game_screen.height - vars->gun.height
					- vars->flash.height / 2;
	i = -1;
	while (error == SUCCESS_CODE && ++i < N_BARS)
		error = load_texture(vars->health_bars + i, bar_path[i], vars->mlx);
	vars->cam.hp = N_BARS - 1;
	return (error);
}

int			init_vars(char *path, t_vars *vars, int save)
{
	int				error;

	init_keys_buffer(vars->keys);
	if ((error = load_cub(path, vars)) != SUCCESS_CODE)
		return (error_print(error));
	if ((error = init_cam(&(vars->cam), &(vars->spawn))) != SUCCESS_CODE)
		return (error_print(error));
	if (!(vars->z_buffer = malloc(sizeof(double) * vars->game_screen.width)))
		return (MALLOC_ERROR);
	if (!(vars->mlx = mlx_init()))
		return (MLX_ERROR);
	check_resolution(vars->mlx,
		&vars->game_screen.width, &vars->game_screen.height);
	if (!save)
		if (!(vars->win = mlx_new_window(vars->mlx,
		vars->game_screen.width, vars->game_screen.height, WIN_NAME)))
			return (MLX_ERROR);
	if ((error = init_img(vars->mlx, vars->game_screen.width,
		vars->game_screen.height, vars->img2)) != SUCCESS_CODE)
		return (error_print(error));
	if ((error = init_img(vars->mlx, vars->game_screen.width,
		vars->game_screen.height, vars->img2 + 1)) != SUCCESS_CODE)
		return (error_print(error));
	return (error_print(init_2(vars)));
}
