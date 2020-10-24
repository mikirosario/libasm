/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functests_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:52:46 by miki              #+#    #+#             */
/*   Updated: 2020/10/24 18:34:56 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_bonus.h"

/*
** Here are some ATOI tests. Feel free to request more. :) Note that this ATOI
** follows the piscine rules, so it is protected against bad bases, but not
** against null strings passed as argument which is undefined. We can refer to
** piscine subject C04, Ex05, with reference to Ex03 for some functionality.
**
** First there are tests that compare my ft_atoi_base with C's atoi with decimal
** conversions and no more than one sign.
**
** Aside from dealing with underflows and overflows (although, from my testing
** it seems that both my and C's atoi deal with overflows the same way anyway,
** we calculate the int as an absolute and tack on the sign after, even if this
** changes the actual value of the number in the process), and handling multiple
** signs and bases, the ft_atoi functionality is the same as the C atoi. C atoi
** segfaults if you send it a null pointer, so mine does as well for null
** pointers to either number or base.
**
** For the other stuff that C's ATOI doesn't do, I just do my tests. I mean,
** it's kind of like strtol, but still different. Numbers can be checked online
** at any nBase - Decimal conversion webpage. Note that binary is a straight
** conversion, not two's complement or anything. So -1 is just -01, etc. So make
** sure the nBase - Decimal conversion you check against is not a two's
** complement system.
**
** Then I do some invalid number and invalid base demonstrations. Note that as
** per the piscine rules, all errors return 0.
*/

void	atoitest(void)
{
	printf("\nFT_ATOI/ATOI COMPARE\n");
	atoicompare();
	printf("\nFT_ATOI BASE CONVERSIONS\n");
	atoibaseconversions();
	printf("\nFT_ATOI INVALID NUMBERS\n");
	invalidnumber();
	printf("\nFT_ATOI INVALID BASES\n");
	invalidbases();
	write(1, RESET, sizeof(RESET));
}

/*
** Creates a simple list, with two members and two datasets, one per member,
** prints the results, and frees the list. The datasets are defined in the
** arguments.
*/

void	pushfronttest(char *data, char *masdata)
{
	t_list	*list;
	t_list	*begin_list;

	list = ft_create_elem(masdata);
	ft_list_push_front(&list, data);
	begin_list = list;
	printf("\nFT_LIST_PUSH_FRONT\n");
	while (list)
	{
		printf(GREEN"My Linked List: %s\n"RESET, (char *)list->data);
		list = list->next;
	}
	freelist(begin_list);
}

/*
** This function simply runs ft_list_size on a list and prints the result. ;)
** Here it is being passed the alphanumeric list we will use to test the rest of
** the linked list functions. That list has all the letters of the alphabet in
** upper and lower case (27 * 2 = 54) and all the numerical single digits (0-9),
** so, 64 members.
*/

void	listsizetest(t_list *list)
{
	printf("\nFT_LIST_SIZE\n");
	printf(GREEN"My List Length: %d\n"RESET, ft_list_size(list));
}

/*
** This is the list sort test. We send the alphabet list with all the jumbled
** letters and numbers to the ft_list_sort function, and it sorts them in ASCII
** order. Before performing the sort, we print the original list for reference
** using the printlist auxiliary function.
*/

void	listsorttest(t_list *list)
{
	printf("\nFT_LIST_SORT\n");
	printf("INITIAL LIST ORDER:\n");
	printf(GREEN);
	printlist(list);
	ft_list_sort(&list, ft_strcmp);
	printf(RESET);
	printf("\nSORTED LIST ORDER:\n");
	printf(GREEN);
	printlist(list);
	printf("\n"RESET);
}

/*
** This is the list_remove_if test. We send it a reference array we want removed
** from the list. We send the ft_list_remove_if function a pointer to the list
** pointer, a reference array to compare against, a pointer to a compare
** function (I use the same ft_strcmp I made in ASM for the obligatory part of
** this project), and a pointer to a free function.
**
** We iterate through the list and free any arrays that match the reference
** string. I'm a civilized individual, so I also NULL the data pointers after
** freeing them. If a data pointer is already NULL, the function skips over it.
*/

void	listremoveiftest(t_list *list, void *remove)
{
	printf("\nFT_REMOVE_IF\n");
	ft_list_remove_if(&list, remove, ft_strcmp, free);
	printf(GREEN);
	printlist(list);
	printf(RESET"\n\n");
}
