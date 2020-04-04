# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/03/30 14:02:39 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

CC = clang

CFLAGS = -Wall -Wextra -lm

RM = rm -rf

DIRSRC = ./

SRC = main.c

OBJ = $(SRC:.c=.o)

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

re: fclean all	

.PHONY: clean fclean
