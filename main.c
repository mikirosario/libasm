/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/13 22:52:34 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

//int		ft_strlen(char *str);
int		ft_write(int fd, const void *buf, size_t nbyte);
//delare ft_read
void	helloworld(void);
void	test(void);

void	testread(int fd)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open("poem.txt", O_RDONLY);
	//test ft_read :P
	close(fd);
}

void	testwrite(int fd, char *string, int bytes)
{
	int res;

	printf("\n\nft_write result: %d\n", (res = ft_write(fd, string, bytes)));
	if (res < 0)
	{
		ft_printf("My Errno: %d\n", errno);
		perror("\0");
	}
	printf("\nC write result: %d\n", (res = write(fd, string, bytes)));
	if (res < 0)
	{
		printf("C's Errno: %d\n", errno);
		perror("\0");
	}
}

/*
** Behaviour if a NULL string is undefined in both strlen and ft_strlen. On
** MacOSX it results in a segfault.
*/

void	teststrlen(char *string)
{
	printf("\n\nft_strlen result: %zu\n", ft_strlen(string));
	printf("\nC strlen result: %zu\n", strlen(string));
}
int	main(void)
{
	//int bytes;
	//int *string;

	//string = NULL;

	//ft_write(1, "\n", 1);
	teststrlen("Hello, world!");
	testwrite(1, NULL, 13);
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