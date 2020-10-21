# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miki <miki@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 20:53:32 by mrosario          #+#    #+#              #
#    Updated: 2020/10/21 23:58:28 by miki             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

UNAME := $(shell uname)

TEST = a.out

# SRC = test.s

SRC = ft_strlen.s ft_write.s ft_read.s ft_strcmp.s ft_strcpy.s ft_strdup.s

BSRC = ft_isspace_bonus.s ft_strchr_bonus.s ft_atoi_base_bonus.s \
ft_create_elem_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s \
ft_list_sort_bonus.s ft_del_bonus.s ft_list_remove_if_bonus.s

LSRC = ft_strlen_linux.s ft_write_linux.s ft_read_linux.s ft_strcmp_linux.s \
ft_strcpy_linux.s ft_strdup_linux.s

LBSRC = ft_isspace_linux_bonus.s ft_strchr_linux_bonus.s ft_atoi_base_linux_bonus.s \
ft_create_elem_linux_bonus.s ft_list_push_front_linux_bonus.s ft_list_size_linux_bonus.s \
ft_list_sort_linux_bonus.s ft_del_linux_bonus.s ft_list_remove_if_linux_bonus.s

ifeq ($(UNAME), Darwin)
FLAGS = -o $(TEST) -Wall -Werror -Wextra
OBJ = $(SRC:.s=.o)
BOBJ = $(BSRC:.s=.o)
%.o: %.s
	nasm -f macho64 $<
endif
	
ifeq ($(UNAME), Linux)
FLAGS = -o $(TEST) -Wall -Werror -Wextra -no-pie -g
OBJ = $(LSRC:.s=.o)
BOBJ = $(LBSRC:.s=.o)
%.o: %.s
	nasm -f elf64 $<
endif

$(LIBFT):
	make -C ./libft
	make clean -C ./libft

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	# make -C ./libft
	# make clean -C ./libft
	# gcc $(FLAGS) -o $(TEST) main.c -I ./libft/ -L ./libft/ -lft -L ./ -lasm
	gcc $(FLAGS) -o $(TEST) main.c -L ./ -lasm

#ld -macosx_version_min 10.14.5 -no_pie -o test $(OBJ) -lSystem

bonus: $(OBJ) $(BOBJ)
	ar rcs $(NAME) $(OBJ) $(BOBJ)
	gcc $(FLAGS) -o $(TEST) main_bonus.c -L ./ -lasm

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(TEST)
	# make fclean -C ./libft

re: fclean all

.PHONY: clean fclean re