# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/07/27 18:57:47 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

HEADERS_PATH = ./includes/

INCLUDES = -I$(HEADERS_PATH) 

CFLAGS = -Wall -Wextra -Werror -O3
RM = rm -rf

DIR = $(shell pwd)

DIRSRC = src

MLX_OPENGL_PATH = ./minilibx_opengl
MLX_LINUX_PATH = ./minilibx_linux

MLX_PATH = 

LIBFT = libft/libftprintf.a

LIB_ARG = 

FRAMEWORKS = 

LINKS = 

UNAME = $(shell uname)

ifeq ($(UNAME),Darwin)
	MLX_PATH = $(MLX_OPENGL_PATH)
	MLX_NAME = libmlx.dylib
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
	LINKS = -L$(MLX_PATH)/
	FRAMEWORKS += -framework OpenGL -framework Appkit
	INCLUDES += -I$(MLX_OPENGL_PATH)
	LOAD_DYLIB = install_name_tool -change $(MLX_NAME) $(DIR)/$(MLX_LIB) $(NAME)
else
	MLX_PATH = $(MLX_LINUX_PATH)
	MLX_NAME = libmlx.a
	INCLUDES += -I$(MLX_LINUX_PATH)
	LINKS += -L$(MLX_PATH) -lXext -lX11 -lxcb -lXau -lXdmcp -lm
	MLX_LIB = $(MLX_PATH)/$(MLX_NAME)
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

OBJDIR = obj

OBJ = $(SRC:$(DIRSRC)/%.c= $(OBJDIR)/%.o)

OBJ_PATHS = $(shell ls -R $(DIRSRC) | grep / | sed 's/://g' | sed 's/src/$(OBJDIR)/g')

HEADERS = $(addprefix $(HEADERS_PATH), \
				cub3d.h events.h frontend.h \
				garbage_collection.h parsing.h raycast.h sprites.h\
			)

OBJBONUS = $(SRCBONUS:.c=.o)

all: $(NAME) $(HEADERS)

$(NAME): $(LIBFT) $(MLX_LIB) $(OBJ)
	@echo COMPILING $(NAME)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) $(MLX_LIB) -o $(NAME) $(LINKS) $(FRAMEWORKS)
	$(LOAD_DYLIB)


$(LIBFT):
	@echo "COMPILING LIBFT"
	$(MAKE) $(LIB_ARG) all -C libft/

$(MLX_LIB):
	@echo "COMPILING MLX"
	$(MAKE) -C $(MLX_PATH)/

$(OBJDIR)/%.o: $(DIRSRC)/%.c $(HEADERS) $(MLX_LIB)
	@mkdir -p $(OBJ_PATHS)
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $< 

clean:
	$(MAKE) -C libft/ clean
	$(MAKE) -C $(MLX_PATH) clean
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	$(MAKE) -C libft/ fclean
	$(RM) $(NAME) 

lilclean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) $(NAME) 

re: fclean all	

.PHONY: clean fclean

opti:
	$(eval CFLAGS += -O3)
	$(eval LIB_ARG += opti)

debug:
	$(eval CFLAGS += -fsanitize=address)
	$(eval LIB_ARG += debug)

QWERTY:
	$(eval CFLAGS += -D QWERTY=1)
