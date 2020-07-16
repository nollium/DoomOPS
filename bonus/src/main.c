/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:49:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/16 19:32:17 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_args(int argc, char **argv)
{
	if (argc != 2 && !(argc == 3 && !ft_strncmp("--save", argv[2], 6)))
	{
		ft_putendl_fd("ERROR: WRONG ARGUMENTS\n\
USAGE : ./cub3D --save (optional) config.cub", 2);
		return (ERROR_CODE);
	}
	return (SUCCESS_CODE);
}

int			main(int argc, char **argv)
{
	t_vars	vars;

	if (check_args(argc, argv) != SUCCESS_CODE)
		return (ERROR_CODE);
	vars = (t_vars){0};
	if ((init_vars(argv[1], &vars, (argc == 3) ? 1 : 0))
		!= SUCCESS_CODE)
	{
		free_vars(&vars);
		return (1);
	}
	vars.img = vars.img2;
	draw_scene(&vars);
	if (argc == 3)
	{
		error_print(write_bmp(SCREENSHOT_PATH, vars.img));
		free_vars(&vars);
		return (0);
	}
	hooks(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	if (LINUX)
		system(MIXER_COMMAND);
	system("(" PLAYER " " MUSIC_PATH BACKGROUND ") " OPTIONS);
	mlx_loop(vars.mlx);
}
