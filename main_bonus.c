/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/24 16:15:47 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"
#include "libasm_bonus.h"

/*
** Frees all members of a linked list of type t_list.
*/

void	freelist(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		ft_del((void *)&list);
		list = tmp;
	}
}

/*
** Frees all datasets of a linked list of type t_list. For use if the memory for
** the datasets was reserved during runtime.
*/

void	freecontent(t_list *list)
{
	while (list)
	{
		if (list->data)
		{
			free(list->data);
			list->data = NULL;
		}
		list = list->next;
	}
}

/*
** Frees all datasets of a linked list of type t_list. Note, use only if the
** datasets were reserved during runtime.
*/

void	printlist(t_list *list)
{
	while (list)
	{
		if (list->data)
			printf("%s", (char *)list->data);
		list = list->next;
	}
}

/*
** Creates a 64-member list consisting of all the letters of the alphabet in
** lower case and upper case in the order they appear on a QWERTY keyboard, and
** the numbers 0 - 9 in jumbled order. This will be to test the list size, the
** the sorting function, and the remove_if function.
*/

t_list	*createalphabetlist(char *qwerty[])
{
	t_list	*list;
	char	*alphabet;
	int		i;

	alphabet = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM9382764501";
	i = 0;
	list = NULL;
	while (i < 64)
	{
		qwerty[i] = malloc(2);
		qwerty[i][0] = alphabet[i];
		qwerty[i][1] = 0;
		i++;
	}
	i = 63;
	while (i >= 0)
	{
		ft_list_push_front(&list, qwerty[i]);
		i--;
	}
	return (list);
}

/*
** Remove preprocessor instruction before evaluation, Norminette doesn't like
** it.
*/

int		main(void)
{
	char	*qwerty[64];
	t_list	*list;

	auxfunctests();
	atoitest();
	pushfronttest("Canario", "Estepario");
	list = createalphabetlist(qwerty);
	listsizetest(list);
	listsorttest(list);
	listremoveiftest(list, "0");
	freecontent(list);
	freelist(list);
#ifdef __APPLE__
	system("leaks a.out");
#endif
	write(1, "\n", 1);
	return (0);
}
