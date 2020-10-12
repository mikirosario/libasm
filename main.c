/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/12 22:26:46 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int		ft_strlen(char *str);
int		ft_write(int fd, const void *buf, size_t nbyte);
void	helloworld(void);
void	test(void);

void	testwrite(int fd, char *string, int bytes)
{
	printf("Write Res: %d\n", (bytes = ft_write(fd, string, bytes)));
	if (bytes < 0)
	{
		printf("My Errno: %d\n", errno);
		perror("\0");
	}
	printf("Write Res: %d\n", (bytes = write(fd, string, bytes)));
	if (bytes < 0)
	{
		printf("C's Errno: %d\n", errno);
		perror("\0");
	}
}


int	main(void)
{
	//int bytes;
	//int *string;

	//string = NULL;
	//printf("Strlen: %d\n", ft_strlen("Hello, world!\n"));
	//ft_write(1, "\n", 1);
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