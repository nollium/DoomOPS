static int	init_sprites_info(t_sprites_sorter *sprites_srt, t_vars *vars)
{
	int		i;

	sprites_srt->sprite_order = malloc(sizeof(int) * vars->num_sprites);
	sprites_srt->sprite_distance = malloc(sizeof(double) * vars->num_sprites);
	if (!(sprites_srt->sprite_distance && sprites_srt->sprite_distance))
		return (ERROR_CODE);
	i = -1;
	while (++i < vars->num_sprites)
	{
		sprites_srt->sprite_order[i] = i;
		sprites_srt->sprite_distance[i] = ((vars->cam.x - vars->sprites[i].x) * (vars->cam.x - vars->sprites[i].x)
							+ (vars->cam.y - vars->sprites[i].y) * (vars->cam.y - vars->sprites[i].y));
	}
	sort_sprites(vars->num_sprites, sprites_srt);
	return (SUCCESS_CODE)
}
