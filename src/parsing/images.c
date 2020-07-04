/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:55:14 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/04 16:31:47 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "frontend.h"

int			load_xpm(t_data *data, char *path, void *mlx)
{
	*data = (t_data){0};
	data->img = mlx_xpm_file_to_image(mlx, path, &(data->width),
										&(data->height));
	if (!data->img)
		return (-1);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
									&(data)->line_length, &(data)->endian);
	return (0);
}

void		img_to_text(t_data *data, t_texture *text)
{
	int	x;
	int	y;

	x = -1;
	text->array = malloc(sizeof(int) * data->width * data->height);
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
}

int			load_texture(t_texture *text, char *path, void *mlx)
{
	t_data data;

	if (load_xpm(&data, path, mlx) == -1)
		return (TEXTURE_ERROR);
	img_to_text(&data, text);
	mlx_destroy_image(mlx, data.img);
	return (SUCCESS_CODE);
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
		sizeof(t_bih), data->width, -data->height, 1, 32, 0, bfh.file_size,
		BMP_DPI * 39.375, BMP_DPI * 39.375, 0, 0
	};
	if ((fd = open(path, O_WRONLY | O_CREAT)) <= 0)
		return (FILE_INVALID_ERROR);
	write(fd, (void *)&bfh, 14);
	write(fd, (void *)&bih, sizeof(t_bih));
	write(fd, data->addr, image_size);
	close(fd);
	return (SUCCESS_CODE);
}
