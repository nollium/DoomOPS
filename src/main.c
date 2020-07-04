/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:49:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/04 17:37:14 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main(int argc, char **argv)
{
	t_vars	vars;

	vars = (t_vars){0};
	if (argc != 2 && !(argc == 3 && !ft_strncmp("--save", argv[1], 6)))
	{
		ft_putendl_fd("ERROR: WRONG ARGUMENTS\n\
USAGE : ./cub3D --save (optional) config.cub", 2);
		return (1);
	}
	if ((init_vars(argv[argc - 1], &vars, (argc == 3) ? 1 : 0))
		!= SUCCESS_CODE)
	{
		free_vars(&vars);
		return (1);
	}
	vars.img = vars.img2;
	draw_scene(&vars);
	system("leaks cub3D");
	if (argc == 3)
	{
		error_print(write_bmp("screenshot.bmp", vars.img));
		free_vars(&vars);
		return (0);
	}
	hooks(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}
