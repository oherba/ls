# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yelazrak <yelazrak@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/05/10 01:56:31 by yelazrak          #+#    #+#              #
#    Updated: 2019/05/12 23:29:13 by yelazrak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS = lsf.c\
		ft_sort.c\
		ft_flag.c\

OBJ =  $(SRCS:.c=.o)
CC = gcc -Wall -Wextra -Werror 

INCLUDE = ft_ls1.h

all: $(NAME)

$(NAME):
	@make  -C libft
	@$(CC) $(SRCS) libft/libft.a -I $(INCLUDE) -o $(NAME)

clean:
	@rm -rf $(OBJ)
	@make clean -C libft

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C libft

re: fclean all