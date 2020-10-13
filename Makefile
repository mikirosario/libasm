# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 20:53:32 by mrosario          #+#    #+#              #
#    Updated: 2020/10/13 22:41:09 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

TEST = a.out

# SRC = test.s

SRC = helloworld.s test.s ft_strlen.s ft_write.s ft_read.s

OBJ = $(SRC:.s=.o)

FLAGS = -Wall -Werror -Wextra

%.o: %.s
	nasm -f macho64 $<

$(LIBFT):
	make -C ./libft
	make clean -C ./libft

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	make -C ./libft
	make clean -C ./libft
	gcc $(FLAGS) -I ./libft/ -L ./ -lasm -L ./libft/ -lft -o $(TEST) main.c

#ld -macosx_version_min 10.14.5 -no_pie -o test $(OBJ) -lSystem

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(TEST)
	make fclean -C ./libft

re: fclean all

.PHONY: clean fclean re