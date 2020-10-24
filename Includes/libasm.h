/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:17:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/24 16:31:02 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <ctype.h>

# define BLUE "\033[1;34m"
# define GREEN "\033[0;32m"
# define RESET "\033[0m"

/*
** Auxiliary ASM Functions
*/

int		ft_isspace(int c);

/*
** Auxiliary C Functions
*/

void	errorcheck(int returnvalue);

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
** Syscall Function Tests
*/

void	testread(int fd, int badbuf, int bytes);
void	testwrite(int fd, char *string, int bytes);

/*
** String Function Tests
*/

void	teststrlen(char *string);
void	teststrcmp(char *s1, char *s2);
void	teststrcpy(char *mydst, char *cdst, char *src);
void	teststrdup(char *src);

#endif
