		for (int stripe = draw.start_x; stripe < draw.end_x; stripe++)
		{
			draw.text_x = (int)(256 * (stripe - (-draw.sprite_width / 2 + draw.sprite_screen_x)) * text->width / draw.sprite_width) / 256;
			//the conditions in the if are:
			//1) it's in front of camera plane so you don't see things behind you
			//2) it's on the screen (left)
			//3) it's on the screen (right)
			//4) vars->z_buffer, with perpendicular distance					

			if (draw.dist < 8 && draw.transform_y > 0 && stripe > 0 && stripe < WINDOW_HEIGHT && draw.transform_y < vars->z_buffer[stripe])
			{
				for(int y = draw.start_y; y < draw.end_y; y++) //for every pixel of the current stripe
				{
					int d = (y) * 256 - WINDOW_HEIGHT * 128 + draw.sprite_height * 128; //256 and 128 factors to avoid floats
					draw.text_y = ((d * text->width) / draw.sprite_height) / 256;
					draw.color = add_shade(draw.dist / MAP_HEIGHT * 2, text->array[text->width * draw.text_y + draw.text_x]);
					my_mlx_pixel_put(vars->img, stripe, y, draw.color);
				}
					vars->redraw = 1;
					vars->seen_sprite = 1;
			}
		