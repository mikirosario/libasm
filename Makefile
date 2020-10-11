# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 20:53:32 by mrosario          #+#    #+#              #
#    Updated: 2020/10/11 21:18:54 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

TEST = a.out

# SRC = test.s

SRC = helloworld.s test.s ft_strlen.s ft_write.s

OBJ = $(SRC:.s=.o)

FLAGS = -Wall -Werror -Wextra

%.o: %.s
	nasm -f macho64 $<

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	gcc $(FLAGS) -L ./ -lasm -o $(TEST) main.c

#ld -macosx_version_min 10.14.5 -no_pie -o test $(OBJ) -lSystem

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(TEST)

.PHONY: clean fclean