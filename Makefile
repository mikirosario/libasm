# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mrosario <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/03 20:53:32 by mrosario          #+#    #+#              #
#    Updated: 2020/10/03 22:07:44 by mrosario         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = test

SRC = test.s

LSRC = linux_test.s

OBJ = $(SRC:.s=.o)

LOBJ = $(LSRC:.s=.o)

$(NAME):
	nasm -f macho64 $(SRC) -o $(OBJ)
	ld -macosx_version_min 10.7.0 -no_pie -o test test.o

linux:
	nasm -f elf64 $(LSRC) -o $(LOBJ)
	ld -m elf_x86_64 $(LOBJ) -o $(NAME)

all: $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)
