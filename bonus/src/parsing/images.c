/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:55:14 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 17:17:00 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "frontend.h"

int			init_img(void *mlx, int width, int height, t_data *img)
{
	*img = (t_data){0};
	if (!(img->img = mlx_new_image(mlx, width, height)))
		return (MLX_ERROR);
	img->addr = mlx_get_data_addr(img->img,
	&(img->bits_per_pixel), &(img->line_length), &(img->endian));
	img->width = width;
	img->height = height;
	return (SUCCESS_CODE);
}

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
	*text = (t_texture){0};
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

	*text = (t_texture){0};
	if (check_file(path) != SUCCESS_CODE)
		return (FILE_INVALID_ERROR);
	if (!text)
		return (TEXTURE_ERROR);
	if (load_xpm(&data, path, mlx) != SUCCESS_CODE)
		return (TEXTURE_ERROR);
	if (!data.addr || data.height <= 0 || data.width <= 0 || !data.img)
		return (MLX_ERROR);
	if ((error = img_to_text(&data, text)) != SUCCESS_CODE)
		*text = (t_texture){0};
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
