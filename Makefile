# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/05 10:47:14 by smaccary          #+#    #+#              #
#    Updated: 2020/07/27 15:05:10 by smaccary         ###   ########.fr        #
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

clean_mandatory:
	$(MAKE) -C $(MANDATORY_PATH) fclean
	$(RM) $(NAME)

fclean: clean
	$(MAKE) -C $(MANDATORY_PATH) fclean
	$(MAKE) -C $(BONUS_PATH) fclean
	$(RM) $(NAME) 

lilclean:
	$(RM) $(OBJ) $(OBJBONUS)
	$(RM) $(NAME) 

re: fclean all

bonus: clean_mandatory
	$(eval CUB_PATH = $(BONUS_PATH))
	$(MAKE) -C $(CUB_PATH) $(MAKE_ARGS) all
	@cp $(CUB_PATH)/$(NAME) .

.PHONY: clean fclean

opti: fclean
	$(eval MAKE_ARGS += opti)

debug:
	$(eval MAKE_ARGS += debug)

QWERTY:
	$(eval MAKE_ARGS += QWERTY)
