# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dirty <dirty@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/07/10 12:39:29 by dirty            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MANDATORY_PATH = ./mandatory

BONUS_PATH = ./bonus

CUB_PATH = $(MANDATORY_PATH)

MAKE = make

MAKE_ARGS = opti

all:
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

clean:
	$(MAKE) -C $(CUB_PATH) clean

fclean: clean
	$(MAKE) -C $(CUB_PATH) fclean
	$(RM) $(NAME) 

lilclean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) $(NAME) 

re: fclean all

bonus:
	$(eval CUB_PATH = $(BONUS_PATH))
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

.PHONY: clean fclean

opti:
	$(eval MAKE_ARGS += opti)

debug: fclean
	$(eval MAKE_ARGS += debug)

QWERTY:
	$(eval MAKE_ARGS += QWERTY)
