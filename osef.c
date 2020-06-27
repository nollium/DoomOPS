int	get_perp_wall_dist(t_cam *cam, t_ray *ray)
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
	return (wall_dist)
}