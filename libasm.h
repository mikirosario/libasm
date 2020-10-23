/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:17:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/23 22:34:39 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

#include "atoitests.h"
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

/*
** Auxiliary ASM Functions
*/

int		ft_isspace(int c);
char	*ft_strchr(char const *s, int c);
t_list	*ft_create_elem(void *data);
void	ft_del(void	**freeme);

/*
** Obligatory ASM Functions
*/

size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
ssize_t	ft_write(int fd, const void *buf, size_t nbyte);
ssize_t ft_read(int fd, void *buf, size_t count);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strcpy(char *dst, const char *src);

/*
** Bonus ASM Functions
*/

int		ft_atoi_base(char *str, char *base);
void	ft_list_push_front(t_list **begin_list, void *data);
int		ft_list_size(t_list *begin_list );
void	ft_list_sort(t_list **begin_list, int (*cmp)());
void	ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void(*free_fct)(void *));

/*
** Test Functions
*/

void	atoicompare(void);
void	atoibaseconversions(void);
void	invalidnumber(void);
void	invalidbases(void);

#endif