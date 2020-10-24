/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/24 18:36:50 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

#define BLUE "\033[1;34m"
#define GREEN "\033[0;32m"
#define RESET "\033[0m"

void	errorcheck(int returnvalue)
{
	if (returnvalue < 0)
	{
		printf("C'S Errno: %d\n", errno);
		perror("\0");
	}
}

int		main(void)
{
	char	*string;
	char	*mydst;
	char	*cdst;

	mydst = calloc(7, 1);
	cdst = calloc(7, 1);
	string = "Hello, world!\n";
	ft_write(1, "\n", 1);
	teststrlen(string);
	testwrite(0, string, ft_strlen(string));
	testread(0, 0, 0);
	teststrcmp("TEST", "Tost");
	teststrcpy(mydst, cdst, "Nivram");
	teststrdup("¡Albricias!");
	printf("\n");
	free(mydst);
	free(cdst);
	mydst = NULL;
	cdst = NULL;
#ifdef __APPLE__
	system("leaks test.out");
#endif
	return (0);
}
