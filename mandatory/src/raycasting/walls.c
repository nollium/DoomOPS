/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 15:30:41 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 00:03:11 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "settings.h"
#include "raycast.h"

static double	get_corner(double angle)
{
	int				i;
	double			max;
	double			corner;
	static double	corner_angle[] = {36.0, 145.0, -38.99999, -142.5};
	double			diff;

	i = -1;
	max = DBL_MAX;
	corner = 0;
	while (++i <= 3)
		if (((diff = fabs(angle - (double)corner_angle[i])) < max))
		{
			max = diff;
			corner = corner_angle[i];
		}
	return (corner);
}

int				get_wall_side(t_vars *vars, t_ray *ray)
{
	double			corner;

	corner = get_corner(atan2((double)ray->y - (double)vars->cam.y,
						(double)ray->x - (double)vars->cam.x) * 180.0 / PI);
	if (corner == 36.0)
		return ((ray->side) ? WEST : NORTH);
	else if (corner == 145.0)
		return ((ray->side) ? WEST : SOUTH);
	else if (corner == -38.99999)
		return ((ray->side) ? EAST : NORTH);
	else if (corner == -142.5)
		return ((ray->side) ? EAST : SOUTH);
	ft_putendl_fd("Weird", 2);
	return (4);
}

long double		get_plane_wall_dist(t_camera *cam, t_ray *ray)
{
	long double	wall_dist;

	if (ray->side == 0)
		wall_dist =
			(ray->x - cam->x + (1.0 - ray->step_x) / 2.0)
				/ ray->dir_x;
	else
		wall_dist =
			(ray->y - cam->y + (1.0 - ray->step_y) / 2.0)
				/ ray->dir_y;
	if (wall_dist == 0)
		wall_dist = 0.01;
	return (wall_dist);
}

void			raycast_walls(t_ray *ray, t_vars *vars, int x)
{
	init_raycast(vars, x, ray);
	get_step(vars, ray);
	perform_dda(vars, ray);
	ray->perp_wall_dist = get_plane_wall_dist(&(vars->cam), ray);
	ray->w_num = get_wall_side(vars, ray);
	get_texture_coords(vars, ray);
	vars->z_buffer[x] = ray->perp_wall_dist;
}
