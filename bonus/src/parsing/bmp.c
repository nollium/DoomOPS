/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/04 17:17:08 by smaccary          #+#    #+#             */
/*   Updated: 2020/08/04 17:29:13 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"
#include "frontend.h"

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
	int			error;

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
