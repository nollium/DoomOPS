/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:55:14 by smaccary          #+#    #+#             */
/*   Updated: 2020/06/14 00:13:01 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		load_xpm(t_data *data, char *path, void *mlx)
{
	*data = (t_data){0}; 
	data->img = mlx_xpm_file_to_image(mlx, path, &(data->width), &(data->height));
    if (!data->img)
        return (-1);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel), &(data)->line_length,
								 &(data)->endian);
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
			text->array[text->width * y + x] = *(unsigned int *)(data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8)));
	}
}
