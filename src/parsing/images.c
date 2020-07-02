/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/26 16:55:14 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/02 18:57:52 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

int			write_bmp(char *path, t_data *data)
{
	int			fd;
	t_texture	img;
	int			height = 11;
	int			width = 24;



	img_to_text(data, &img);
	fd = open(path, O_WRONLY);
	int pad = (4 - (width * 3) % 4) % 4;
	int image_size = width * height;
	//int file_size = 54 + 3 * image_size;
	int file_size = 54 + (3 * (width + pad) * height);
	int ppm = 72 * 39.375;
	struct bitmap_file_header {
		unsigned char   bitmap_type[2];     // 2 bytes
	    int             file_size;          // 4 bytes
	    short           reserved1;          // 2 bytes
	    short           reserved2;          // 2 bytes
	    unsigned int    offset_bits;        // 4 bytes
	} bfh;
	// bitmap image header (40 bytes)
	struct bitmap_image_header {
		 unsigned int    size_header;        // 4 bytes
	    unsigned int    width;              // 4 bytes
	    unsigned int    height;             // 4 bytes
	    short int       planes;             // 2 bytes
	    short int       bit_count;          // 2 bytes
	    unsigned int    compression;        // 4 bytes
	    unsigned int    image_size;         // 4 bytes
	    unsigned int    ppm_x;              // 4 bytes
	    unsigned int    ppm_y;              // 4 bytes
	    unsigned int    clr_used;           // 4 bytes
	    unsigned int    clr_important;      // 4 bytes
	} bih;
	// if you are on Windows you can include <windows.h>
	// and make use of the BITMAPFILEHEADER and BITMAPINFOHEADER structs
	ft_memcpy(&bfh.bitmap_type, "BM", 2);
	bfh.file_size       = file_size;
	bfh.reserved1       = 0;
	bfh.reserved2       = 0;
	bfh.offset_bits     = 0;
	
	bih.size_header     = sizeof(bih);
	bih.width           = width;
	bih.height          = height;
	bih.planes          = 1;
	bih.bit_count       = 32;
	bih.compression     = 0;
	bih.image_size      = file_size;
	bih.ppm_x           = ppm;
	bih.ppm_y           = ppm;
	bih.clr_used        = 0;
	bih.clr_important   = 0;
	fd = open(path, O_WRONLY);
	// compiler woes so we will just use the constant 14 we know we have
	write(fd, (void *)&bfh, 14);
	write(fd, (void *)&bih, sizeof(bih));
	/*fwrite(&bfh, 1, 14, image);
	fwrite(&bih, 1, sizeof(bih), image);*/
	// write out pixel data, one last important this to know is the ordering is backwards
	// we have to go BGR as opposed to RGB
	unsigned char color[3] = {0,0,255,0};
	unsigned char zeros[10] = {0,0,0,0,0,0,0,0,0,0};
	int j = -1;
	for (int i = 0; i < image_size; i++)
	{
		if (i > 200)
			color[0] = 255; 
		write(fd, color, 4);
		//write(fd, zeros, pad);
	}
	close(fd);
}