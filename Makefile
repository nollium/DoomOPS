# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/05/01 13:07:44 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -lm -g -fsanitize=address

RM = rm -rf

DIRSRC = ./

SRC = main.c frontend.c handlers.c backend.c init.c raycast.c keyboard_handler.c \
colors_handling.c

OBJ = $(SRC:.c=.o)

HEADERS = cub3D.h

OBJBONUS = $(SRCBONUS:.c=.o)

LIBFT = libft/libftprintf.a

all: $(NAME)

bonus: $(OBJBONUS) $(NAME)
	ar rcs $(NAME) $(OBJBONUS)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -L/usr/local/lib -lmlx -lXext -lX11 -lpthread -lxcb -lXau -lXdmcp -lbsd


$(LIBFT):
	$(MAKE) -C libft/

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
