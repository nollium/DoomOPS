# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dirty <dirty@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/07/11 13:52:18 by dirty            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

MANDATORY_PATH = ./mandatory

BONUS_PATH = ./bonus

CUB_PATH = $(MANDATORY_PATH)

MAKE = make

MAKE_ARGS =

all:
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

clean:
	$(MAKE) -C $(MANDATORY_PATH) clean
	$(MAKE) -C $(BONUS_PATH) clean


fclean: clean
	$(MAKE) -C $(MANDATORY_PATH) fclean
	$(MAKE) -C $(BONUS_PATH) fclean
	$(RM) $(NAME) 

lilclean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) $(NAME) 

re: fclean all

bonus: fclean
	$(eval CUB_PATH = $(BONUS_PATH))
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

.PHONY: clean fclean

opti:
	$(eval MAKE_ARGS += opti)
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

debug:
	$(eval MAKE_ARGS += debug)
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

QWERTY:
	$(eval MAKE_ARGS += QWERTY)
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .
