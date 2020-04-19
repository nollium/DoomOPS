/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:51:48 by smaccary          #+#    #+#             */
/*   Updated: 2020/04/19 16:58:44 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
 #define CUB3D_H
 #include <time.h>
 #include <unistd.h>
 #include <mlx.h>
 #include <math.h>
 #include <X11/Xlib.h>
 #include <fcntl.h>
 #include "libft/libftprintf.h"

 #define K_BUFF_SIZE		20
 #define WINDOW_WIDTH		400
 #define WINDOW_HEIGHT		400
 #define WALLS_SIZE			64
 #define FOV 				60
 #define WALL_COLOR			0x00FFFFFF
 #define WALL_SIDE_COLOR	0x00FF0000
 #define ROOF_COLOR			0x0000FFFF
 #define FLOOR_COLOR		0x00A0522D
 #define PLAYER_HEIGHT		32
 #define MAP_WIDTH 			24
 #define MAP_HEIGHT 		24
 #define MAP_PATH			"./map.cub"
 
 #define FORWARD_KEY		122
 #define BACKWARD_KEY		115
 #define LEFT_KEY			113
 #define RIGHT_KEY			100
 #define SPEED				0.03
 #define TURN_SPEED			0.036

 #define SPAWN_X			3
 #define SPAWN_Y			2

/*
** SCREEN_DIST = (SCREEN_WIDTH) / (tan(FOV / 2) * 2)
*/

 #define SCREEN_DIST 277

typedef struct	s_ray
{
	double		dir_x;
	double		dir_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
}				t_ray;

typedef struct	s_plane
{
	double		x;
	double		y;
}				t_plane;

/*
** PLAYER CAMERA 
*/

typedef struct	s_camera
{
	double		x;
	double		y;
	double		dir_x;
	double		dir_y;
	t_plane		plane;
	double		scene[WINDOW_WIDTH];
}				t_camera;

/*
**  s_data CONTAINS ALL THE DATA RELATED TO AN MLX IMAGE 
*/

typedef struct  s_data
{
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
}               t_data;

/*
** KEY STRUCT WITH THE LENGTH OF TIME THE KEY HAS BEEN PRESSED 
*/

typedef struct  s_keys
{
	int         keycode;
	time_t      time;
}               t_keys;

typedef struct	s_wall
{
	int			x[2];
	int			y[2];
	int			color;
}				t_wall;

typedef struct s_map
{
	char		**array;
	t_wall		**walls;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_map;


typedef struct  s_vars
{
	void        *mlx;
	void        *win;
	t_map		map;
	t_data      *img;
	t_data      img2;
	t_camera	cam;
	t_keys      keys[K_BUFF_SIZE + 1];
}               t_vars;

/*
** INIT 
*/

void			init_vars(int width, int height, t_vars *vars);

/*
** RAYCAST 
*/

t_ray 			raycast(t_vars *vars, int x);


/*
** FRONTEND 
*/

int		        create_trgb(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 			my_line_put(t_data *data, int x0, int y0, int x1, int y1, int color);
void			drawRectangle(t_data *data, int top_left[2], int bot_right[2]);
void			drawcircle(t_data *data, int x0, int y0, int radius, int color);
void			drawhalfcircle(t_data *data, int x0, int y0, int radius, int color);
void			draw_gradient(t_data *data);
void			draw_rainbow(t_data *data);

void		draw_scene(t_vars *vars);


/*
** EVENT HANDLERS 
*/

void    		hooks(t_vars *vars);
int				loop_handler(t_vars *vars);
int         	key_handler(int keycode, t_vars *vars);
int				mouse_handler(int button, int x, int y, t_vars *vars);
int				move_handler(void);
int				resize_handler(void);
int				enter_handler(void);
int				leave_handler(void);
int				release_handler(int keycode, t_vars *vars);

#endif