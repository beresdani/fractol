# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dberes <dberes@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/23 15:49:50 by grherman          #+#    #+#              #
#    Updated: 2023/11/17 17:22:27 by dberes           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Werror -Wextra -g
LIBFT =-Llibft/ -lft
NAME = fractol
SRC = fractol.c fract_utils.c
MLX=-lXext -lX11 -lz -lm -lmlx
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) libft/libft.a
	cc $(OBJ) -o $(NAME) libft/libft.a $(MLX)
	
# create o files
%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

#run Makefile in libft folder
libft/libft.a:
	$(MAKE) -C libft all

clean:
	rm -rf $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
	$(MAKE) -C libft re

.PHONY: clean fclean cleanup re all

