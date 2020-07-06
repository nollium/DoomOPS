# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/07/06 15:28:47 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

HEADERS_PATH = ./includes/

INCLUDES = -I$(HEADERS_PATH) 

CFLAGS = -Wall -Wextra -g3

RM = rm -rf

DIRSRC = ./src

MLX_OPENGL_PATH = ./minilibx_opengl
MLX_LINUX_PATH = ./minilibx_linux

MLX_PATH = 

LIBFT = libft/libftprintf.a

LIB_ARG = 

LINKS = -lmlx

FRAMEWORKS = 

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	MLX_PATH = $(MLX_OPENGL_PATH)
	MLX_LIB = $(MLX_PATH)/libmlx.dylib
	LINKS = -L$(MLX_PATH)/
	FRAMEWORKS += -framework OpenGL -framework Appkit
	INCLUDES += -I$(MLX_OPENGL_PATH)
	EXPORT_DYLIB = export DYLD_LIBRARY_PATH=$(MLX_OPENGL_PATH)/$$DYLD_LIBRARY_PATH
else
	MLX_PATH = $(MLX_LINUX_PATH)
	INCLUDES += -I$(MLX_LINUX_PATH)
	LINKS += -lmlx -lXext -lX11 -lxcb -lXau -lXdmcp -lm
endif

SRC = $(addprefix $(DIRSRC)/, \
			main.c \
\
			$(addprefix parsing/,\
			backend.c  init.c parsing.c images.c map.c sprites_parsing.c) \
\
			raycasting/raycast.c raycasting/walls.c\
\
			$(addprefix frontend/,\
			colors_handling.c frontend.c draw_scene.c)\
\
			$(addprefix sprites/,\
			sprites_sort.c  init_sprites.c sprites.c)\
\
			garbage_collection/garbage_collector.c \
\
			$(addprefix events/,\
			loop.c  handlers.c  keyboard_handler.c keyboard.c) \
\
			debug/debug_map.c debug/errors.c \
		)

OBJDIR = ./obj

OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)

HEADERS = $(addprefix $(HEADERS_PATH), \
				cub3d.h events.h frontend.h \
				garbage_collection.h parsing.h raycast.h sprites.h\
			)

OBJBONUS = $(SRCBONUS:.c=.o)

all: $(NAME) $(HEADERS)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	export DYLD_LIBRARY_PATH=$(MLX_OPENGL_PATH)/$$DYLD_LIBRARY_PATH
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME) $(LINKS) $(FRAMEWORKS)

$(LIBFT):
	$(MAKE) $(LIB_ARG) all -C libft/

$(MLX_LIB):
	$(MAKE) -C $(MLX_PATH)/

$(OBJDIR)/%.o: $(DIRSRC)/%.c $(HEADERS) $(MLX_LIB)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

clean:
	$(MAKE) -C libft/ clean
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	$(MAKE) -C libft/ fclean
	$(RM) $(NAME) 

lilclean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) $(NAME) 

re: fclean all	

.PHONY: clean fclean

show:
	echo $(OBJ)

opti:
	$(eval CFLAGS += -Ofast)
	$(eval LIB_ARG += opti)

debug:
	$(eval CFLAGS += -fsanitize=address)
	$(eval LIB_ARG += debug)

QWERTY:
	$(eval CFLAGS += -D QWERTY=1)
