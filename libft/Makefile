# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/04/04 19:33:25 by smaccary         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = clang

CFLAGS = -Wall -Wextra -g3 -O3

RM = rm -rf

DIRSRC = ./

SRC = lib/ft_bzero.c lib/ft_isalnum.c lib/ft_isalpha.c lib/ft_isascii.c lib/ft_isdigit.c \
lib/ft_isprint.c lib/ft_memccpy.c lib/ft_memcpy.c lib/ft_memchr.c lib/ft_memmove.c \
lib/ft_memset.c  lib/ft_strlcat.c lib/ft_strlcpy.c lib/ft_strlen.c \
lib/ft_strncmp.c lib/ft_strnstr.c lib/ft_strrchr.c lib/ft_strchr.c lib/ft_tolower.c \
lib/ft_toupper.c lib/ft_memcmp.c lib/ft_strnlen.c lib/ft_atoi.c lib/ft_strdup.c \
lib/ft_calloc.c lib/ft_split.c lib/ft_strjoin.c lib/ft_substr.c lib/ft_strtrim.c \
lib/ft_itoa.c lib/ft_strmapi.c lib/ft_putchar_fd.c lib/ft_putstr_fd.c lib/ft_putendl_fd.c \
lib/ft_putnbr_fd.c lib/ft_lstnew.c lib/ft_lstadd_front.c lib/ft_lstsize.c \
lib/ft_lstlast.c lib/ft_lstadd_back.c lib/ft_lstdelone.c lib/ft_lstclear.c \
lib/ft_lstiter.c lib/ft_lstmap.c lib/ft_lstcpy.c \
ft_printf.c  ft_putnbr_base.c printspace.c wrappers.c\
ft_getptr.c get_conv.c get_infos.c print_form.c printconv.c\
lib/get_next_line.c

OBJ = $(SRC:.c=.o)

OBJBONUS = $(SRCBONUS:.c=.o)

all: $(NAME)

bonus: $(OBJBONUS) $(NAME)
	ar rcs $(NAME) $(OBJBONUS)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ) $(LIBFT)

obj/%.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all	

.PHONY: clean fclean
