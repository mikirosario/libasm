# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 20:53:32 by mrosario          #+#    #+#              #
#    Updated: 2020/10/16 22:35:27 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

UNAME := $(shell uname)

TEST = a.out

# SRC = test.s

SRC = helloworld.s test.s ft_strlen.s ft_write.s ft_read.s ft_strcmp.s ft_strcpy.s ft_strdup.s

LSRC = ft_write_linux.s ft_read_linux.s ft_strlen_linux.s

ifeq ($(UNAME), Darwin)
FLAGS = -o $(TEST) -Wall -Werror -Wextra
OBJ = $(SRC:.s=.o)
%.o: %.s
	nasm -f macho64 $<
endif
	
ifeq ($(UNAME), Linux)
FLAGS = -o $(TEST) -Wall -Werror -Wextra -no-pie
OBJ = $(LSRC:.s=.o)
%.o: %.s
	nasm -f elf64 $<
endif

$(LIBFT):
	make -C ./libft
	make clean -C ./libft

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	make -C ./libft
	make clean -C ./libft
	gcc $(FLAGS) -o $(TEST) main.c -I ./libft/ -L ./libft/ -lft -L ./ -lasm

#ld -macosx_version_min 10.14.5 -no_pie -o test $(OBJ) -lSystem

linux:
	nasm -f elf64 $(LSRC) -o $(LOBJ)
	ld -m elf_x86_64 $(LOBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(TEST)
	make fclean -C ./libft

re: fclean all

.PHONY: clean fclean re