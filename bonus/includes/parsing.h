/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dirty <dirty@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:44:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/22 04:34:17 by dirty            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <fcntl.h>
# include <unistd.h>
# include "structs/structs.h"
# include "../libft/libftprintf.h"
# include "garbage_collection.h"
# include "settings.h"

# define ASPECT_RATIO 0.6

# define GUN_PATH   "pics/small_gun.xpm"
# define FLASH_PATH "pics/muzzle.xpm"

# define BAR_1_PATH "pics/bars/bar_2_.xpm"
# define BAR_2_PATH	"pics/bars/bar_3_.xpm"
# define BAR_3_PATH	"pics/bars/bar_4_.xpm"
# define BAR_4_PATH	"pics/bars/bar_5_.xpm"
# define BAR_5_PATH	"pics/bars/bar_6_.xpm"
# define BAR_6_PATH	"pics/bars/bar_7_.xpm"

# define VALID_CONF_IDS		"NSWEFC\n"
# define VALID_MAP_CHARS	"01234NSEW "
# define CONF_FILE_EXTENSION ".cub"
# define WIN_NAME "cub3D"
# define STDERR 2

/*
**  IMAGE PARSING
*/

int		init_img(void *mlx, int width, int height, t_data *img);
int		load_xpm(t_data *data, char *path, void *mlx);
int		load_texture(t_texture *text, char *path, void *mlx);
int		img_to_text(t_data *data, t_texture *text);

/*
**  Reusable conf parsing function
*/

int		check_resolution(void *mlx, int *width, int *height);
int		parse_resolution(char *line, t_screen *screen);
int		parse_color(char *line);

/*
**  Cub3D specific functions
*/
int		check_borders(char **map);
int		find_spawn(char **map, t_spawn *spawn);
char	**parse_array(t_list *lst, int len);
int		init_vars(char *path, t_vars *vars, int save);
int		load_cub(char *path, t_vars *vars);
int		parse_sprites(t_vars *vars, char **map, int *size);

#endif
