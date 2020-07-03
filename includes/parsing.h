/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/18 14:44:02 by smaccary          #+#    #+#             */
/*   Updated: 2020/07/02 14:28:27 by smaccary         ###   ########.fr       */
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

# define VALID_CONF_IDS		"NSWEFC\n"
# define VALID_MAP_CHARS	"012NSEW "

/*
** PARSING
*/

int		find_spawn(char **map, t_spawn *spawn);
char	**parse_array(t_list *lst, int len);
int		parse_resolution(char *line, t_screen *screen);
int		parse_color(char *line);
int		load_xpm(t_data *data, char *path, void *mlx);
int		load_texture(t_texture *text, char *path, void *mlx);
void	img_to_text(t_data *data, t_texture *text);
int		init_vars(char *path, t_vars *vars, int save);
int		load_cub(char *path, t_vars *vars);
int		parse_sprites(t_vars *vars, char **map, int *size);

#endif
