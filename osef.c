int			write_bmp(char *path, t_data *data)
{
	int			fd;
	int			image_size;
	t_bfh		bfh;
	t_bih		bih;

	image_size = data->width * data->height * data->bits_per_pixel / 8;
	bfh = (t_bfh){{'B', 'M'}, BMP_HEADER_SIZE + image_size, 0, 0, 0};
	bih = (t_bih)
	{
		sizeof(t_bih), data->width, data->height, 1, 32, 0, bfh.file_size,
		BMP_DPI * 39.375, BMP_DPI * 39.375, 0, 0
	};
	if ((fd = open(path, O_WRONLY | O_CREAT)) <= 0)
		return (FILE_INVALID_ERROR);
	write(fd, (void *)&bfh, 14);
	write(fd, (void *)&bih, sizeof(t_bih));
	write(fd, data->addr , image_size);
	close(fd);
	printf("file_size :%d\n", bfh.file_size);
	return (SUCCESS_CODE);
}