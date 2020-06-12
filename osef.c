static int	get_corner_angle(t_map *map, t_camera *cam)
{
	int		i;
	double	angle;
	double	max;
	double	corner;
	static int	corner_angle[] = {45, 145, -55, -135};
	double		diff;


	i = -1;
	angle = atan2(vars->map.y - (double)vars->cam.y, (double)vars->map.x
		- (double)vars->cam.x) * 180.0 / PI;
	max = DBL_MAX;
	while (++i <= 3)
		if (((diff = fabs(angle - (double)corner_angle[i])) < max))
		{
			max = diff;
			corner = corner_angle[i];
		}
}