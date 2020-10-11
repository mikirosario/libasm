/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/11 22:14:11 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int		ft_strlen(char *str);
int		ft_write(int fd, const void *buf, size_t nbyte);
void	helloworld(void);
void	test(void);

int	main(void)
{
	printf("Strlen: %d\n", ft_strlen("Hello, world!"));
	printf("Write Res: %d\n", ft_write(1, "Hola, mundo!\n", 13));
	return (0);
}