# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/06/17 17:57:00 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -g3 

RM = rm -rf

DIRSRC = ./

SRC =	main.c frontend.c handlers.c backend.c init.c raycast.c keyboard_handler.c	\
		colors_handling.c images.c loop.c sprites_sort.c init_sprites.c sprites.c	\
		garbage_collector.c parsing.c

OBJ = $(SRC:.c=.o)

HEADERS = cub3D.h

OBJBONUS = $(SRCBONUS:.c=.o)

LIBFT = libft/libftprintf.a

LIB_ARG = 

DEBUG = -O3

all: $(NAME) $(HEADERS)	

bonus: $(OBJBONUS) $(NAME)
	ar rcs $(NAME) $(OBJBONUS)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L/usr/local/lib -lmlx -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lbsd -lm


$(LIBFT):
	$(MAKE) $(LIB_ARG) -C libft/

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
	$(eval LIB_ARG += -O3)

debug:
	$(eval CFLAGS += -fsanitize=address)
	$(eval LIB_ARG += -fsanitize=address)
