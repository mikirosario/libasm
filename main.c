/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/18 18:13:30 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

# define BLUE "\033[1;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
ssize_t	ft_write(int fd, const void *buf, size_t nbyte);
ssize_t ft_read(int fd, void *buf, size_t count);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
int		ft_isspace(int c);


void	errorcheck(int returnvalue)
{
	if (returnvalue < 0)
	{
		printf("C'S Errno: %d\n", errno);
		perror("\0");
	}
}

/*
** This is a read tester that tests my ft_read against C's read. It uses a test
** file called poem.txt where I poured my heart out. I will be deeply offended
** if you laugh at my poetry. It prints out the poem to terminal using both my
** and C's read.
**
** If you set fd at 0 it will open the file and get the real fd. If you send
** any other fd it will use -1 to test the fd error.
**
** If you set buf at 0 it will use the address of a char as the buf. If you
** set it at any other number, it will use a NULL pointer as buf to test the bad
** address error.
**
** If you set bytes at 0, it will use a single byte as its buffer. If you set
** it at any other number, it will use -1 as the bytes to read, to test the bad
** argument error.
**
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
** You send fd, string and bytes to both ft_write and write, and it prints the
** result (bytes written) as well as doing the write. If you send bad parameters
** (-1 or NULL string), it will refer to errno and print the associated errors
** for both functions.
**
** The errors will be printed just after the writes to ensure they're valid.
** Then the results are printed.
**
** Note, if the bytes (third) parameter is bad, MacOSX syscall will throw a
** Bad parameter error, whilst Ubuntu Linux will, weirdly, throw a Bad address
** error. Don't fault the messenger, I'm just a go-between. ;)
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

/*
** Behaviour with a NULL string is undefined in both strlen and ft_strlen. On
** MacOSX it results in a segfault.
*/

void	teststrlen(char *string)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\nMy Strlen:\nft_strlen result: %zu\n", ft_strlen(string));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strlen\nC strlen result: %zu\n", strlen(string));
	write(1, RESET, sizeof(RESET));
}

void	teststrcmp(char *s1, char *s2)
{
	ft_write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Strcmp:\n%d\n", ft_strcmp(s1, s2));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strcmp:\n%d\n", strcmp(s1, s2));
	write(1, RESET, sizeof(RESET));
}

/*
** We pass two pointers to destination strings defined in the main, and a
** source string from which to copy, then print the destination strings after
** the copy is made. We do the copy first with my ft_strcpy and copy to mydst,
** then with C's strcpy and copy to cdst.
*/

void	teststrcpy(char *mydst, char *cdst, char *src)
{
	ft_write(1, GREEN, sizeof(GREEN));
	ft_strcpy(mydst, src);
	printf("\n\nMy Strcpy:\n%s\n", mydst);
	write(1, BLUE, sizeof(BLUE));
	strcpy(cdst, src);
	printf("\nC's Strcpy:\n%s\n", cdst);
	write(1, RESET, sizeof(RESET));
}

/*
** We pass a source string to the function and use both ft_strdup (first) and
** strdup (second) to do a copy, print the copy and, of course, free the copy.
** If the copy fails both functions should set an ENOMEM error in errno. This
** can be tested for my function, but the only way I know to do it currently
** is modifying the strdup source code before compilation to throw the error
** in case of success, so as to force it onto the error branch. I can't do that
** for the original strdup, of course (well, I mean... I COULD attempt to hack
** the binary, I guess... but I don't know, it seems just a tad overkill. xD).
**
** As with some other functions, there is no protection against NULL strings in
** the original strdup, so there is also no such protection in ft_strdup. The
** behaviour in that case is undefined, and in MacOSX it leads to a predictable
** segfault.
**
** If anyone knows a more elegant way to test the malloc failure condition,
** please do enlighten me!
*/

void	teststrdup(char *src)
{
	char *cpy;
	cpy = ft_strdup(src);
	ft_write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Strdup:\n");
	if (cpy)
	{
		printf("%s\n", cpy);
		free(cpy);
		cpy = NULL;
	}
	else
		perror(0);
	cpy = strdup(src);
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strdup:\n");
	if (cpy)
	{
		printf("%s\n", cpy);
		free(cpy);
		cpy = NULL;
	}
	else
		perror(0);
	write(1, RESET, sizeof(RESET));
}

int	main(void)
{
	char *string;
	char mydst[] = {"Marvin"};
	char cdst[] = {"Marvin"};

	string = "Hello, world!\n";
	ft_write(1, "\n", 1);
	teststrlen(string);
	testwrite(0, string, ft_strlen(string));
	testread(0, 0, 0);
	teststrcmp("TEST", "Tost");
	teststrcpy(mydst, cdst, "Nivram");
	teststrdup("¡Albricias!");
	return (0);
}