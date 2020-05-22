		draw.start = -(draw.line_height) / 2 + WINDOW_HEIGHT / 2;
		draw.start = (draw.start < 0) ? 0 : draw.start;
		draw.end = (draw.line_height) / 2 + WINDOW_HEIGHT / 2;
		draw.end = (draw.end >= WINDOW_HEIGHT) ? WINDOW_HEIGHT - 1 : draw.end;
		draw.color = ROOF_COLOR;