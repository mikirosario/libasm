/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/15 22:52:57 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

# define BLUE "\033[1;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

//int		ft_strlen(char *str); Already defined in libft
int		ft_write(int fd, const void *buf, size_t nbyte);
ssize_t ft_read(int fd, void *buf, size_t count);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
void	helloworld(void);
void	test(void);


void	errorcheck(int returnvalue)
{
	if (returnvalue < 0)
	{
		ft_printf("C'S Errno: %d\n", errno);
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
	ft_write(1, GREEN"\nMy Read:\n", 10 + sizeof(GREEN));
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
	ft_write(1, "\n", 1);
	res = ft_write(fd, string, bytes);
	errorcheck(res);
	ft_printf("ft_write result: %d\n", res);
	ft_write(1, BLUE, sizeof(BLUE));
	write(1, "\n", 1);
	res = write(fd, string, bytes);
	errorcheck(res);
	ft_printf("C write result: %d\n", res);
	ft_write(1, RESET, sizeof(RESET));
}

/*
** Behaviour with a NULL string is undefined in both strlen and ft_strlen. On
** MacOSX it results in a segfault.
*/

void	teststrlen(char *string)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\nMy strlen:\nft_strlen result: %zu\n", ft_strlen(string));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's strlen\nC strlen result: %zu\n", strlen(string));
	write(1, RESET, sizeof(RESET));
}

void	teststrcmp(char *s1, char *s2)
{
	ft_write(1, GREEN, sizeof(GREEN));
	printf("\nMy Strcmp: %d\n", ft_strcmp(s1, s2));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strcmp: %d\n", strcmp(s1, s2));
	write(1, RESET, sizeof(RESET));
}

/*void	teststrcpy(char *s1a, char *s1b, char *s2a, char *s2b)
{
	
	ft_write(1, GREEN, sizeof(GREEN));
	ft_strcpy(s1a, s1b);
	printf("\n%s\n", s1a);
	write(1, BLUE, sizeof(BLUE));
	strcpy(s2a, s2b);
	printf("\n%s\n", s2a);
	write(1, RESET, sizeof(RESET));
}*/

int	main(void)
{
	//int bytes;
	char *string;
	char test[15];
	char test2[15];

	string = "Hello, world!\n";
	ft_write(1, "\n", 1);
	teststrlen(string);
	testwrite(0, string, ft_strlen(string));
	testread(0, 0, 0);
	teststrcmp("TEST", "Tost");
	ft_strcpy(test, "Hello, world!");
	printf("\n%s\n", test);
	strcpy(test2, "Hello, world!");
	printf("\n%s\n", test2);
	/*printf("Write Res: %d\n", (bytes = ft_write(1, string, 13)));
	if (bytes < 0)
	{
		printf("My Errno: %d\n", errno);
		perror("\0");
	}
	printf("Write Res: %d\n", (bytes = write(1, string, 13)));
	if (bytes < 0)
	{
		printf("C's Errno: %d\n", errno);
		perror("\0");
	}*/
	return (0);
}