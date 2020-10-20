/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/20 22:50:44 by mrosario         ###   ########.fr       */
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
#include <string.h>

# define BLUE "\033[1;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

typedef struct		s_list
 {
	 void			*data;
	 struct	s_list	*next;
 }					t_list;

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
ssize_t	ft_write(int fd, const void *buf, size_t nbyte);
ssize_t ft_read(int fd, void *buf, size_t count);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);
int		ft_isspace(int c);
char	*ft_strchr(char const *s, int c);
int		ft_atoi_base(char *str, char *base);
t_list	*ft_create_elem(void *data);
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list );
int		ft_list_sort(t_list **begin_list);

void	errorcheck(int returnvalue)
{
	if (returnvalue < 0)
	{
		printf("C'S Errno: %d\n", errno);
		perror("\0");
	}
}


int	main(void)
{
	char data[] = {"Canario"};
	char masdata[] = {"Estepario"};
	t_list	*list;
	ft_write(1, "\n", 1);

	printf("\nT: %d, N: %d, V: %d, F: %d, R: %d, Sp: %d\n", '\t', '\n', '\v', \
	'\f', '\r', ' ');
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Isspace: %d\n", ft_isspace(' '));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Isspace: %d\n", isspace(' '));
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Strchr: %s\n", ft_strchr("find", 'f'));
	printf("My Strchr: %s\n", ft_strchr("find", 'p'));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strchr: %s\n", strchr("find", 'f'));
	printf("C's Strchr: %s \n", strchr("find", 'p'));
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Ft_atoi_base: %d\n", ft_atoi_base("--++-+11010100010101basurilla", "01"));
	printf("\n\nMy Ft_atoi_base: %d\n", ft_atoi_base("--++-+-2147483648basurilla", "0123456789"));
	list = ft_create_elem(masdata);
	ft_list_push_front(&list, data);
	printf("\n\nMy Linked List: %s, %s\n", (char *)list->data, (char *)list->next->data);
	printf("\n\nMy List Length: %d\n", ft_list_size(list));
	write(1, RESET, sizeof(RESET));
	printf("\nTEST\n");
	//printf("\n%d\n", ft_list_sort(&list));
	while (list)
	{
		free(list);
		list = list->next;
	}

	return (0);
}