/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/15 15:49:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/02 14:43:19 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			main(int argc, char **argv)
{
	t_vars	vars;

	vars = (t_vars){0};
	if (argc != 2)
	{
		ft_putendl_fd("ERROR: WRONG ARGUMENTS\nUSAGE : ./cub3D config.cub", 2);
		return (1);
	}
	if ((init_vars(argv[1], &vars)) != SUCCESS_CODE)
	{
		free_vars(&vars);
		return (1);
	}
	vars.img = vars.img2;
	draw_scene(&vars);
	write_bmp("screenshot.bmp", vars.img);
	return (0);
	hooks(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img->img, 0, 0);
	mlx_loop(vars.mlx);
}
