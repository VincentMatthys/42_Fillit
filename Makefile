# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmatthys <vmatthys@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/28 22:07:13 by vmatthys          #+#    #+#              #
#    Updated: 2016/12/01 19:21:51 by vmatthys         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

OBJ_DIR = obj
SRC_PATH = srcs/fillit
OBJ_PATH = $(OBJ_DIR)/fillit
SRC_NAME += main.c
SRC_NAME += leonardo.c
SRC_NAME += leader.c
OBJ_NAME = $(SRC_NAME:.c=.o)
SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
CC = gcc
LIBFT_PATH = srcs/libft/
LIB_DIR = lib/
LDFLAGS = -L$(LIB_DIR)
LDLIBS = -lft
CFLAGS = -Wall -Werror -Wextra
CPPFLAGS = -Iincludes/
DIR = $(OBJ_DIR) $(LIB_DIR) $(OBJ_PATH)
NAME = fillit

.PHONY : all clean fclean re
export LIB_DIR
export OBJ_DIR

all : $(DIR) $(NAME)

$(DIR) :
	mkdir -p $@

$(NAME) : $(DIR) $(OBJ)
	make -C $(LIBFT_PATH)
	$(CC) $(LDFLAGS) $(LDLIBS) $(OBJ) -o $@

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

clean :
	make -C $(LIBFT_PATH) $@
	rm -f $(OBJ)
	@rmdir $(OBJ_PATH) $(OBJ_DIR) 2> /dev/null || true

fclean :
	make -C $(LIBFT_PATH) $@
	rm -f $(OBJ)
	rm -f $(NAME)
	@rmdir $(OBJ_PATH) $(LIB_DIR) $(OBJ_DIR) 2> /dev/null || true

re : fclean all
