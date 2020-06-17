void		draw_col(t_vars *vars, t_drawer *draw)
{
	while (++draw->y < draw->screen->height)
	{
		if (draw->start <= draw->y && draw->y <= draw->end)
		{
			get_color(draw, &(vars->text[draw->side]));
			//draw->color = (vars->w_color) ? vars->w_color : draw->color;
			if (SHADOW_MODE)	
				draw->color = add_shade(((double)draw->dist / 16 * 2), draw->color);
		}
		if (draw->y > draw->end)
		{
			draw->color = FLOOR_COLOR;
			if (SHADOW_MODE)
				draw->color = add_shade(1.05 / ((double)draw->y * 2.15 / (double)((draw->screen->height))) , draw->color);
		}
		my_mlx_pixel_put(vars->img, draw->x, draw->y, draw->color);
	}
}