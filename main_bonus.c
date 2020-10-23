/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/23 22:42:55 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

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
** This function simply tests the auxiliary functions that the bonus functions
** will depend on to work properly. These are ft_isspace and ft_strchr, which
** are compared against isspace and strchr, respectively. These aren't bonus
** functions themselves, but the bonus functions do depend on them, so if you
** can break them, you can probably break one or more of my bonus functions. :)
**
** Don't be shy! If I have bugs, I deserve it! xD
**
** Note that printf should be tolerant of being passed a null string pointer and
** behave by printing (null), but my Linux compiler is not. ;) It thinks it's
** pretty clever and seems to detect that this will happen and throws an error
** over it with -Werror enabled. Hence, when running this on Linux, instead of
** sending the null to printf as a string type, I send it as a pointer address
** type, so it prints (nil) and the Linux compiler quits bothering me. ;)
*/

void	bonusdependencytest(void)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Isspace: %d\n", ft_isspace(' '));
	printf("My Isspace: %d\n", ft_isspace('p'));
	write(1, BLUE, sizeof(BLUE));
	printf("C's Isspace: %d\n", isspace(' '));
	printf("C's Isspace: %d\n", isspace('p'));
	write(1, GREEN, sizeof(GREEN));
	printf("\nMy Strchr: %s\n", ft_strchr("find", 'f'));
	printf("My Strchr: %s\n", ft_strchr("find", 'i'));
	printf("My Strchr: %s\n", ft_strchr("find", 'n'));
	printf("My Strchr: %s\n", ft_strchr("find", 'd'));
	printf("My Strchr: %s\n", ft_strchr("find", '\0')); // In this case mine returns NULL ptr instead of ptr to the null char, must fix.
	printf("My Strchr: %s\n", ft_strchr("find", 'p'));
	write(1, BLUE, sizeof(BLUE));
	printf("C's Strchr: %s\n", strchr("find", 'f'));
	printf("C's Strchr: %s\n", strchr("find", 'i'));
	printf("C's Strchr: %s\n", strchr("find", 'n'));
	printf("C's Strchr: %s\n", strchr("find", 'd'));
	printf("C's Strchr: %s\n", strchr("find", '\0'));
	#ifdef __APPLE__
	printf("C's Strchr: %s \n", strchr("find", 'p'));
	#else
	printf("C's Strchr: %p \n", strchr("find", 'p'));
	#endif
	write(1, RESET, sizeof(RESET));
}

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
**
*/

void	atoitest(void)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nFT_ATOI/ATOI COMPARE\n");
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
	while(list)
	{
		printf(GREEN"\nMy Linked List: %s "RESET, (char *)list->data);
		list = list->next;
	}
	freelist(begin_list);
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
		char 	alphabet[] = \
		{"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM9382764501"};
		int		i;

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
** This is the list sort test. We send the alphabet list with all the jumbled
** letters to the ft_list_sort function, and it sorts them in ASCII order.
*/

void	listsorttest(t_list *list)
{
	printf(GREEN"\nINITIAL LIST ORDER:\n");
	printlist(list);
	ft_list_sort(&list, ft_strcmp);
	printf("\nSORTED LIST ORDER:\n");
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

void	listremoveiftest(t_list *list, char *remove)
{
	printf(GREEN"REMOVE APPLIED:\n");
	ft_list_remove_if(&list, remove, ft_strcmp, free);
	printlist(list);
	printf("\n"RESET);
}

int	main(void)
{
	char	*qwerty[64];
	t_list	*list;


	printf("\nT: %d, N: %d, V: %d, F: %d, R: %d, Sp: %d\n", '\t', '\n', '\v', \
	'\f', '\r', ' ');
	bonusdependencytest();
	atoitest();
	pushfronttest("Canario", "Estepario");
	list = createalphabetlist(qwerty);
	printf(GREEN"\n\nMy List Length: %d\n"RESET, ft_list_size(list));
	listsorttest(list);
	listremoveiftest(list, "0");
	freecontent(list);
	freelist(list);
	system("leaks a.out"); // 1 16-byte leak, definitely a struct member...
	return (0);
}