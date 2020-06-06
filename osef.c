		//calculate width of the sprite
		draw.width = fabs((WINDOW_HEIGHT / (draw.transform_y)));
		draw.start_x = -draw.width / 2 + draw.sprite_screen_x;
		if (draw.start_x < 0)
			draw.start_x = 0;
		draw.end_x = draw.width / 2 + draw.sprite_screen_x;
		if (draw.end_x >= WINDOW_WIDTH)
			draw.end_x = WINDOW_WIDTH - 1;