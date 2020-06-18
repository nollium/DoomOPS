# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/06/18 17:56:06 by smaccary         ###   ########.fr        #
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
			parsing/backend.c  parsing/init.c  parsing/parsing.c \
			parsing/images.c \
\
			raycasting/raycast.c \
\
			frontend/colors_handling.c  frontend/frontend.c \
\
			sprites/sprites_sort.c  sprites/init_sprites.c \
			sprites/sprites.c \
\
			garbage_collection/garbage_collector.c \
\
			events/loop.c  events/handlers.c  events/keyboard_handler.c \
		)


OBJ = $(SRC:.c=.o)




HEADERS = $(addprefix $(INCLUDES), \
				cub3D.h events.h frontend.h \
				garbage_collection.h parsing.h raycast.h sprites.h\
			)

OBJBONUS = $(SRCBONUS:.c=.o)

LIBFT = libft/libftprintf.a

LIB_ARG = 


all: $(NAME) $(HEADERS)	

bonus: $(OBJBONUS) $(NAME)
	ar rcs $(NAME) $(OBJBONUS)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L/usr/local/lib -lmlx -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lbsd -lm


$(LIBFT):
	$(MAKE) $(LIB_ARG) all -C libft/

obj/%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

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
	$(eval CFLAGS += -O3)
	$(eval LIB_ARG += opti)

debug:
	$(eval CFLAGS += -fsanitize=address)
	$(eval LIB_ARG += debug)
