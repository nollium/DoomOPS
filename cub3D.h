/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 12:51:48 by smaccary          #+#    #+#             */
/*   Updated: 2020/05/24 21:27:19 by smaccary         ###   ########.fr       */
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
 #include <stdint.h>

# define WARNINGS 1
# define WARN_LEVEL 100000
# define DEBUG_MODE 0
# define SHADOW_MODE 1

 #define WINDOW_WIDTH		600
 #define WINDOW_HEIGHT		600

 #define MAP_WIDTH 			24
 #define MAP_HEIGHT 		24
 #define MAP_PATH			"./map.cub"

 #define WALL_COLOR			0x00AAAAAA
 #define WALL_SIDE_COLOR	0x00888888

// #define ROOF_COLOR			0xFF99FFFF
 #define ROOF_COLOR			0x00000000
 #define FLOOR_COLOR		0x009C9C9C
// #define FLOOR_COLOR		0x0099FFFF
 
 #define K_BUFF_SIZE		20
 
 #define FORWARD_KEY		122
 #define BACKWARD_KEY		115
 #define LEFT_KEY			113
 #define RIGHT_KEY			100
 #define CTRL_KEY			65507
 #define ALT_KEY			65513
 #define C_KEY				99

 #define SPEED				0.1
 #define TURN_SPEED			0.1
 #define ALT_MULT			2

 #define SPAWN_X			2
 #define SPAWN_Y			2

/*
** SCREEN_DIST = (SCREEN_WIDTH) / (tan(FOV / 2) * 2)
*/

 #define SCREEN_DIST 277

typedef struct	s_ray
{
	long double	dir_x;
	long double	dir_y;
	long double	side_dist_x;
	long double	side_dist_y;
	long double	delta_dist_x;
	long double	delta_dist_y;
	long double	perp_wall_dist;

	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	int			line_height;
}				t_ray;

typedef struct	s_plane
{
	long double		x;
	long double		y;
}				t_plane;

typedef struct	s_pxl
{
	int			x;
	int			y;
	int			color;
}				t_pxl;


/*
** PLAYER CAMERA 
*/

typedef struct	s_camera
{
	long double		x;
	long double		y;
	long double		dir_x;
	long double		dir_y;
	double			speed;
	double			turn_speed;
	t_plane			plane;
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
	int			height;
	int			width;
}               t_data;

/*
** KEY STRUCT WITH THE LENGTH OF TIME THE KEY HAS BEEN PRESSED 
*/

typedef struct  s_keys
{
	int         keycode;
	time_t      time;
}               t_keys;

typedef struct	s_map
{
	int			x;
	int			y;
	char 		worldMap[MAP_WIDTH][MAP_HEIGHT];
}				t_map;


typedef struct	s_texture
{
	int			*array;
	int			width;
	int			height;
	int			x;
	int			y;
}				t_texture;

typedef struct	s_drawer
{
	int			start;
	int			end;
	int			color;
	int			line_height;
	int			x;
	int			y;
	int			dist;
	int			side;
	double 		step;
	double		tex_pos;
	
}				t_drawer;


typedef struct  s_vars
{
	void        *mlx;
	void        *win;
	t_map		map;
	t_data      *img;
	t_data      img2;
	t_camera	cam;
	t_keys      keys[K_BUFF_SIZE + 1];
	t_texture	text;
}               t_vars;

int				 add_shade(double dist, int color);

/*
** INIT 
*/		

void			init_vars(int width, int height, t_vars *vars);

/*
** RAYCAST 
*/

t_ray			raycast(t_ray *ray, t_vars *vars, int x);

/*
** BACKEND 
*/

t_keys			*key_chr(t_keys *arr, int keycode, size_t size);


/*
** FRONTEND 
*/
void			draw_text(t_texture *text, t_data *img);
int				rgb_to_trgb(unsigned char t, int rgb);
int		        create_trgb(unsigned char a, unsigned char r, unsigned char g, unsigned char b);
void            my_mlx_pixel_put(t_data *data, int x, int y, int color);
void 			my_line_put(t_data *data, int x0, int y0, int x1, int y1, int color);
void			drawRectangle(t_data *data, int top_left[2], int bot_right[2]);
void			drawcircle(t_data *data, int x0, int y0, int radius, int color);
void			drawhalfcircle(t_data *data, int x0, int y0, int radius, int color);
void			draw_gradient(t_data *data);
void			draw_rainbow(t_data *data);

void			draw_scene(t_vars *vars);


/*
** EVENT HANDLERS 
*/
int				keyboard_handler(t_vars *vars);
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