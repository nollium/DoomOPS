	double angle = atan2(3.0 - (double)vars->cam.y, 4.0 - (double)vars->cam.x) * 180.0 / PI;
	double diff;
	double max;
	int corner;
	static int	corner_angle[] = {45, 145, -55, -135};
	int i;
//	printf("angle : %lf && ray->side = %d\n", angle, ray->ray->side);
	
	i = -1;
	max = DBL_MAX;
	while (++i < 3)
		if (((diff = fabs(angle - (double)corner_angle[i])) < max))
		{
			max = diff;
			corner = corner_angle[i];
		}

	if (corner == 45)
		vars->w_color = (ray->side) ? WEST : NORTH;
	else if (corner == 145)
		vars->w_color = (ray->side) ? WEST : SOUTH;
	else if (corner == -55)
		vars->w_color = (ray->side) ? EAST : NORTH;
	else if (corner == -135)
		vars->w_color = (ray->side) ? EAST : SOUTH;


static void	get_wall_side(t_vars *vars, t_ray *ray)
{
	double		angle;
	double		diff;
	double		max;
	int			corner;
	static int	corner_angle[] = {45, 145, -55, -135};
	int			i;

//	printf("angle : %lf && ray->side = %d\n", angle, ray->ray->side);
	i = -1;
	angle = atan2(3.0 - (double)vars->cam.y, 4.0 - (double)vars->cam.x) * 180.0 / PI;
	max = DBL_MAX;
	while (++i < 3)
		if (((diff = fabs(angle - (double)corner_angle[i])) < max))
		{
			max = diff;
			corner = corner_angle[i];
		}

	if (corner == 45)
		vars->w_color = (ray->side) ? WEST : NORTH;
	else if (corner == 145)
		vars->w_color = (ray->side) ? WEST : SOUTH;
	else if (corner == -55)
		vars->w_color = (ray->side) ? EAST : NORTH;
	else if (corner == -135)
		vars->w_color = (ray->side) ? EAST : SOUTH;
}