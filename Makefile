# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/06/26 20:26:11 by user42           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

INCLUDES = ./includes/

CFLAGS = -Wall -Wextra -I$(INCLUDES) -g3 

RM = rm -rf

DIRSRC = ./src/

SRC = $(addprefix $(DIRSRC), \
			main.c \
\
			$(addprefix parsing/,\
			backend.c  init.c parsing.c images.c map.c sprites_parsing.c) \
\
			raycasting/raycast.c \
\
			frontend/colors_handling.c  frontend/frontend.c \
\
			$(addprefix sprites/,\
			sprites_sort.c  init_sprites.c sprites.c)\
\
			garbage_collection/garbage_collector.c \
\
			$(addprefix events/,\
			loop.c  handlers.c  keyboard_handler.c) \
\
			debug/debug_map.c \
		)

OBJDIR = ./obj/

OBJ = $(SRC:.c=.o)
#$(SRC:./src/%.c=./bin/%.o)
#$(SRC:.c=.o)

HEADERS = $(addprefix $(INCLUDES), \
				cub3d.h events.h frontend.h \
				garbage_collection.h parsing.h raycast.h sprites.h\
			)

OBJBONUS = $(SRCBONUS:.c=.o)

LIBFT = libft/libftprintf.a

LIB_ARG = 

LINKS = -lmlx

FRAMEWORKS = 

all: $(NAME) $(HEADERS)	

#clang -Wall -Wextra -I./includes/ -g3 -o cub3D $(OBJ) libft/libftprintf.a -L/usr/local/lib -lmlx -lXext -lX1 -lxcb -lXau -lXdmcp -lm
	#$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L/usr/local/lib -lmlx -lXext -lX11 -lXau -lXdmcp -lm 

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L/usr/local/lib $(LINKS) $(FRAMEWORKS)
$(LIBFT):
	$(MAKE) $(LIB_ARG) all -C libft/

#$(OBJ): $(SRC) $(HEADERS)
obj/%.o: $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) -c $(SRC) -o $@


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

opti:
	$(eval CFLAGS += -Ofast)
	$(eval LIB_ARG += opti)

debug:
	$(eval CFLAGS += -fsanitize=address)
	$(eval LIB_ARG += debug)

OSX:
	$(eval CFLAGS += -D OS_OSX=1)
	$(eval FRAMEWORKS += -framework OpenGL -framework Appkit)

UBUNTU:
	$(eval CFLAGS += -D OS_UBUNTU=1)
	$(eval LINKS += -lmlx -lXext -lX11 -lxcb -lXau -lXdmcp -lm)

QWERTY:
	$(eval CFLAGS += -D QWERTY=1)