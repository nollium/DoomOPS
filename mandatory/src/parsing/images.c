/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:55:14 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 00:00:55 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "frontend.h"
#include <stdint.h>

int			load_xpm(t_data *data, char *path, void *mlx)
{
	if (!data || !path || check_file(path) != SUCCESS_CODE)
		return (NULL_ERROR);
	if (!mlx)
		return (MLX_ERROR);
	*data = (t_data){0};
	data->img = mlx_xpm_file_to_image(mlx, path, &(data->width),
										&(data->height));
	if (!data->img)
		return (FILE_INVALID_ERROR);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
									&(data)->line_length, &(data)->endian);
	return (SUCCESS_CODE);
}

int			img_to_text(t_data *data, t_texture *text)
{
	int	x;
	int	y;

	x = -1;
	if (!(text->array = malloc(sizeof(int) * data->width * data->height)))
		return (MALLOC_ERROR);
	text->width = data->width;
	text->height = data->height;
	while (++x < text->width)
	{
		y = -1;
		while (++y < text->height)
			text->array[text->width * y + x] = *(unsigned int *)
			(data->addr + (y * data->line_length + x *
			(data->bits_per_pixel / 8)));
	}
	return (SUCCESS_CODE);
}

int			load_texture(t_texture *text, char *path, void *mlx)
{
	t_data	data;
	int		error;

	if (check_file(path) != SUCCESS_CODE)
		return (FILE_INVALID_ERROR);
	if (!text)
		return (TEXTURE_ERROR);
	if (load_xpm(&data, path, mlx) != SUCCESS_CODE)
		return (TEXTURE_ERROR);
	if (!data.addr || data.height <= 0 || data.width <= 0 || !data.img)
		return (MLX_ERROR);
	error = img_to_text(&data, text);
	mlx_destroy_image(mlx, data.img);
	return (error);
}

/*
** Unused functions
** void		reverse_img(t_data *data)
** {
** 	int start;
** 	int end;
** 	int tmp;
**
** 	start = 0;
** 	end = data->bits_per_pixel / 8 * data->width * data->height;
** 	while (start < end)
** 	{
** 		tmp = *(int *)(data->addr + start);
** 		*(int *)(data->addr + start) = *(int *)(data->addr + end);
** 		*(int *)(data->addr + end) = tmp;
** 		start += sizeof(int);
** 		end -= sizeof(int);
** 	}
** }
**
** void		flip_img(t_data *data)
** {
** 	int				y;
** 	int				x;
** 	int				tmp;
** 	int				*ptr;
** 	int				*dst;
**
** 	x = -1;
** 	while (++x < data->width / 2)
** 	{
** 		y = -1;
** 		while (++y < data->height)
** 		{
** 			ptr = (int *)(data->addr + (y * data->line_length
**  + x * (data->bits_per_pixel / 8)));
** 			tmp = *ptr;
** 			dst = (int *)(data->addr + (y * data->line_length
**  + (data->width - x) * (data->bits_per_pixel / 8)));
** 			*ptr = *dst;
** 			*dst = tmp;
** 		}
** 	}
** }
*/

static int	write_bmp_headers(int fd, t_data *data)
{
	int		image_size;
	char	bfh[14];
	t_bih	bih;

	image_size = data->width * data->height * data->bits_per_pixel / 8;
	bfh[0] = 'B';
	bfh[1] = 'M';
	*(uint32_t *)(bfh + 2) = BMP_HEADER_SIZE + image_size;
	*(uint32_t *)(bfh + 2 + 8) = 54;
	bih = (t_bih){sizeof(t_bih), data->width, -data->height, 1, 32, 0,
	image_size + BMP_HEADER_SIZE, BMP_DPI * 39.375, BMP_DPI * 39.375, 0, 0};
	if (write(fd, (void *)bfh, 14) != 14
	|| write(fd, (void *)&bih, sizeof(t_bih)) != sizeof(t_bih))
		return (ERROR_CODE);
	return (SUCCESS_CODE);
}

int			write_bmp(char *path, t_data *data)
{
	int			fd;
	int			image_size;
	t_texture	text;
	int 		error;

	if ((fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0666)) <= 0)
		return (FILE_INVALID_ERROR);
	if ((error = write_bmp_headers(fd, data)) != SUCCESS_CODE)
		return (error);
	image_size = data->width * data->height * data->bits_per_pixel / 8;
	img_to_text(data, &text);
	if (text.array)
	{
		if (write(fd, (char *)(text.array), image_size) != image_size)
			error = ERROR_CODE;
	}
	else
		error = MALLOC_ERROR;
	close(fd);
	free(text.array);
	return (error);
}
