void		init_cam(t_camera *cam, char spawn_direction)
{
	static t_camera	cam_switcher[] = {
		(t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, 0.66}},
		(t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, 0.66}},
		(t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, 0.66}},
		(t_camera){SPAWN_X, SPAWN_Y, -1.0, 0.0, SPEED, TURN_SPEED,
		(t_plane){0, 0.66}},};
	char			*dir_str;
	int				i;
	dir_str = "NSEW";
	i = -1;
	while (dir_str[++i] && dir_str[i] != spawn_direction)
        ;
	
}