void		init_img(void *mlx, int width, int height, t_data *img)
{
	img->img = mlx_new_image(mlx, width, height);
	img->addr = mlx_get_data_addr(img->img,
	&(img->bits_per_pixel), &(img).line_length,
								 &(img).endian);
	img->width = width;
	img->height = height;
}