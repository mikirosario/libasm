/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syscalltests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 14:53:02 by miki              #+#    #+#             */
/*   Updated: 2020/10/24 16:17:06 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** This function tests my syscall read wrapper function ft_read against C's
** equivalent read. It uses a test file called poem.txt where I poured my heart
** out. I will be deeply offended if you laugh at my poetry! It prints out the
** poem to terminal using both my ft_read and C's read. The read syscall is akin
** to get_next_line, except it doesn't seem to have anything against '\n'. :p I
** use it to retrieve the file byte by byte as it isn't very big.
**
** If you set fd at 0 it will open the file and get the real fd. If you send
** any other fd it will use -1 to test the fd error.
**
** If you set buf at 0 it will use the address of a local char as buf. If you
** set it at any other number, it will use a NULL pointer as buf to test the bad
** address error.
**
** If you set bytes at 0, it will declare its buffer size as 1 byte buffer (the
** char we're using as our buffer). If you set it at any other number, it will
** declare -1 as the bytes to read, to test the bad argument error.
**
** For  both my function and C's function errorcheck will be called upon exit
** from the while for any reason (EOF or error). If it detects that an error was
** thrown, it will reference errno and print the error.
*/

void	testread(int fd, int badbuf, int bytes)
{
	char	c;
	char	*buf;
	int		res;

	res = 0;
	fd = !fd ? open("poem.txt", O_RDONLY) : -1;
	buf = !badbuf ? &c : NULL;
	bytes = !bytes ? 1 : -1;
	ft_write(1, GREEN"\n\nMy Read:\n", 10 + sizeof(GREEN));
	while ((res = ft_read(fd, buf, bytes)) > 0)
		if (*buf)
			printf("%c", *buf);
	errorcheck(res);
	lseek(fd, 0, SEEK_SET);
	write(1, BLUE"\nC's Read:\n", 11 + sizeof(BLUE));
	while ((res = read(fd, buf, bytes)) > 0)
		if (*buf)
			printf("%c", *buf);
	errorcheck(res);
	if (fd > 2)
		close(fd);
	write(1, RESET, sizeof(RESET));
}

/*
** This function tests my syscall write wrapper function ft_write against C's
** equivalent write.
**
** You send fd, string and bytes to both ft_write and write, and it prints the
** result (bytes written) as well as doing the write. If you send bad parameters
** (-1 or NULL string), it will refer to errno and print the associated errors
** for both functions.
**
** The errors will be printed just after the writes to ensure they're valid.
** Errorcheck will print the errno error if an error was thrown. Then the
** results are printed.
**
** Note, if the bytes (third) parameter is bad, MacOSX syscall will throw a
** Bad parameter error, whilst Ubuntu Linux will, weirdly, throw a Bad address
** error instead. You goofed, Canonical. ;) Don't fault the messenger, I'm just
** a go-between here. ;)
*/

void	testwrite(int fd, char *string, int bytes)
{
	int res;

	ft_write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Write:\n");
	res = ft_write(fd, string, bytes);
	errorcheck(res);
	printf("ft_write result: %d\n", res);
	ft_write(1, BLUE, sizeof(BLUE));
	printf("\nC's Write:\n");
	res = write(fd, string, bytes);
	errorcheck(res);
	printf("C write result: %d\n", res);
	ft_write(1, RESET, sizeof(RESET));
}
