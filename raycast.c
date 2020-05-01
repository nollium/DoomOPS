/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 21:24:35 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/01 10:58:16 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_raycast(t_vars *vars, int x, t_ray *ray, long double *camera_x)
{
	*camera_x = 2 * x / (long double)WINDOW_WIDTH - 1.0;
	ray->dir_x = vars->cam.dir_x + vars->cam.plane.x * *camera_x;
	ray->dir_y = vars->cam.dir_y + vars->cam.plane.y * *camera_x;
	vars->map.x = (int)(vars->cam.x);
	vars->map.y = (int)(vars->cam.y);
	ray->delta_dist_x = fabsl(1 / ray->dir_x);
	ray->delta_dist_y = fabsl(1 / ray->dir_y);
	ray->hit = 0;
}

static void	get_step(t_vars *vars, t_ray *ray)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1.0;
		ray->side_dist_x = (vars->cam.x - vars->map.x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1.0;
		ray->side_dist_x =
			(vars->map.x + 1.0 - vars->cam.x) * ray->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1.0;
		ray->side_dist_y = (vars->cam.y - vars->map.y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1.0;
		ray->side_dist_y =
			(vars->map.y + 1.0 - vars->cam.y) * ray->delta_dist_y;
	}
}

static void	perform_dda(t_vars *vars, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			vars->map.x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			vars->map.y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map.worldMap[vars->map.x][vars->map.y] - '0' > 0)
			ray->hit = 1;
	}
}

static void	get_wall_dist(t_vars *vars, t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist =
			(vars->map.x - vars->cam.x + (1.0 - ray->step_x) / 2.0)
				/ ray->dir_x;
	else
		ray->perp_wall_dist =
			(vars->map.y - vars->cam.y + (1.0 - ray->step_y) / 2.0)
				/ ray->dir_y;
}

t_ray		raycast(t_vars *vars, int x)
{
	t_ray		ray;
	long double	camera_x;

	init_raycast(vars, x, &ray, &camera_x);
	get_step(vars, &ray);
	perform_dda(vars, &ray);
	get_wall_dist(vars, &ray);
	return (ray);
}
