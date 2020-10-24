# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 20:53:32 by mrosario          #+#    #+#              #
#    Updated: 2020/10/24 18:39:52 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libasm.a

UNAME := $(shell uname)

TEST = test.out

SRC = ft_strlen.s ft_write.s ft_read.s ft_strcmp.s ft_strcpy.s ft_strdup.s

CSRC = syscalltests.c strfunctests.c

BSRC = ft_isspace_bonus.s ft_strchr_bonus.s ft_atoi_base_bonus.s \
ft_create_elem_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s \
ft_list_sort_bonus.s ft_del_bonus.s ft_list_remove_if_bonus.s

BCSRC = atoitests_bonus.c auxfunctests_bonus.c functests_bonus.c

LSRC = ft_strlen_linux.s ft_write_linux.s ft_read_linux.s ft_strcmp_linux.s \
ft_strcpy_linux.s ft_strdup_linux.s

LBSRC = ft_isspace_linux_bonus.s ft_strchr_linux_bonus.s ft_atoi_base_linux_bonus.s \
ft_create_elem_linux_bonus.s ft_list_push_front_linux_bonus.s ft_list_size_linux_bonus.s \
ft_list_sort_linux_bonus.s ft_del_linux_bonus.s ft_list_remove_if_linux_bonus.s

ifeq ($(UNAME), Darwin)
FLAGS = -I ./Includes/ -o $(TEST) -Wall -Werror -Wextra
OBJ = $(addprefix ./asm_src/,$(SRC:.s=.o))
BOBJ = $(addprefix ./asm_src/bonus/,$(BSRC:.s=.o))
%.o: %.s
	nasm -f macho64 $<
endif
	
ifeq ($(UNAME), Linux)
FLAGS = -I ./Includes/ -o $(TEST) -Wall -Werror -Wextra -no-pie -g
OBJ = $(addprefix ./linux/,$(LSRC:.s=.o))
BOBJ = $(addprefix ./linux/,$(LBSRC:.s=.o))
%.o: %.s
	nasm -f elf64 $<
endif

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)
	gcc $(FLAGS) -o $(TEST) $(addprefix ./c_src/,$(CSRC)) main.c -L ./ -lasm

bonus: $(OBJ) $(BOBJ)
	ar rcs $(NAME) $(OBJ) $(BOBJ)
	gcc $(FLAGS) -o $(TEST) $(addprefix ./c_src/bonus/,$(BCSRC)) main_bonus.c -L ./ -lasm

all: $(NAME)

clean:
	rm -f ./asm_src/*.o
	rm -f ./asm_src/bonus/*.o

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re