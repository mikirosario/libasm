/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:17:46 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/24 16:30:25 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_BONUS_H
# define LIBASM_BONUS_H

# include "libasm.h"
# include "atoitests.h"

typedef	struct		s_list
{
	void			*data;
	struct s_list	*next;
}					t_list;

/*
** Auxiliary C Functions
*/

void				freelist(t_list *list);
void				printlist(t_list *list);

/*
** More Auxiliary ASM Functions
*/

t_list				*ft_create_elem(void *data);
char				*ft_strchr(char const *s, int c);
void				ft_del(void	**freeme);

/*
** Bonus ASM Functions
*/

int					ft_atoi_base(char *str, char *base);
void				ft_list_push_front(t_list **begin_list, void *data);
int					ft_list_size(t_list *begin_list);
void				ft_list_sort(t_list **begin_list, int (*cmp)());
void				ft_list_remove_if(t_list **begin_list, void *data_ref, \
int (*cmp)(), void(*free_fct)(void *));

/*
** ATOI Test Functions
*/

void				auxfunctests(void);
void				atoitest(void);
void				atoicompare(void);
void				atoibaseconversions(void);
void				invalidnumber(void);
void				invalidbases(void);

/*
** Linked List Test Functions
*/

void				pushfronttest(char *data, char *masdata);
void				listsizetest(t_list *list);
void				listsorttest(t_list *list);
void				listremoveiftest(t_list *list, void *remove);

#endif
