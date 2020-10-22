/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 21:34:11 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/22 22:56:19 by mrosario         ###   ########.fr       */
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
	printf("\nT: %d, N: %d, V: %d, F: %d, R: %d, Sp: %d\n", '\t', '\n', '\v', \
	'\f', '\r', ' ');
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
** Aside from dealing with underflows and overflows (although, from my testing
** it seems that both my and C's atoi deal with overflows the same way anyway,
** we calculate the int as an absolute and tack on the sign after, even if this
** changes the actual value of the number in the process), and handling multiple
** signs and bases, the atoi functionality is the same as the C atoi. C atoi
** segfaults if you send it a null pointer, so mine does as well for null
** pointers.
**
** The first several tests are basic decimal conversions compared against C's
** ATOI - of course for mine we must specify the decimal base, but otherwise
** it's equivalent.
**
** For the other stuff that C's ATOI doesn't do, I just do my tests. I mean,
** it's kind of like strtol, but still different. Numbers can be checked online
** at any nBase - Decimal conversion webpage. Note that binary is a straight
** conversion, not two's complement or anything. So -1 is just -01, etc. So make
** sure the nBase - Decimal conversion you check against is not a two's
** complement system.
*/

void	atoitest(void)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nFT_ATOI/ATOI COMPARE\n");
	printf("ft_atoi_base\t(\"  \\t-42\", \"0123456789\")\t\t\t %d\n", ft_atoi_base("  \t-42", "0123456789"));
	printf(BLUE"atoi\t\t(\"  \\t-42\")\t\t\t\t\t %d\n"GREEN, atoi("  \t-42"));
	printf("ft_atoi_base\t(\"  \\t\\n\\r\\v\\f  42\", \"0123456789\")\t\t %d\n", ft_atoi_base("  \t\n\r\v\f  42", "0123456789"));
	printf(BLUE"atoi\t\t(\"  \\t\\n\\r\\v\\f  42\")\t\t\t\t %d\n"GREEN, atoi("  \t\n\r\v\f  42"));
	printf("ft_atoi_base\t(\"    +42\", \"0123456789\")\t\t\t %d\n", ft_atoi_base("    +42", "0123456789"));
	printf(BLUE"atoi\t\t(\"    +42\")\t\t\t\t\t %d\n"GREEN, atoi("    +42"));
	printf("ft_atoi_base\t(\" \\n\\v\\f -0\", \"0123456789\")\t\t\t %d\n", ft_atoi_base(" \n\v\f -0", "0123456789"));
	printf(BLUE"atoi\t\t(\" \\n\\v\\f -0\")\t\t\t\t\t %d\n"GREEN, atoi(" \n\v\f -0"));
	printf("ft_atoi_base\t(\"0\", \"0123456789\")\t\t\t\t %d\n", ft_atoi_base("0", "0123456789"));
	printf(BLUE"atoi\t\t(\"0\")\t\t\t\t\t\t %d\n"GREEN, atoi("0"));
	printf("ft_atoi_base\t(\"1\", \"0123456789\")\t\t\t\t %d\n", ft_atoi_base("1", "0123456789"));
	printf(BLUE"atoi\t\t(\"1\")\t\t\t\t\t\t %d\n"GREEN, atoi("1"));
	printf("ft_atoi_base\t(\"-2147483648basurilla\", \"0123456789\")\t\t %d\n", ft_atoi_base("-2147483648basurilla", "0123456789"));
	printf(BLUE"atoi\t\t(\"-2147483648basurilla\")\t\t\t %d\n"GREEN, atoi("-2147483648basurilla"));
	printf("ft_atoi_base\t(\"-2147483647basurilla\", \"0123456789\")\t\t %d\n", ft_atoi_base("2147483647basurilla", "0123456789"));
	printf(BLUE"atoi\t\t(\"-2147483647basurilla\")\t\t\t %d\n"GREEN, atoi("2147483647basurilla"));
	printf("\nFT_ATOI BASE CONVERSIONS\n");
	printf("ft_atoi_base\t(\"--++-+11010100010101basurilla\", \"01\")\t\t %d\n", ft_atoi_base("--++-+11010100010101basurilla", "01"));
	printf("ft_atoi_base\t(\"--++-+-2147483648basurilla\", \"0123456789\")\t %d\n", ft_atoi_base("--++-+-2147483648basurilla", "0123456789"));
	printf("ft_atoi_base\t(\"ff\", \"0123456789abcdef\")\t\t\t %d\n", ft_atoi_base("ff", "0123456789abcdef"));
	printf("ft_atoi_base\t(\"1411\", \"01234567\")\t\t\t\t %d\n", ft_atoi_base("1411", "01234567"));
	printf("ft_atoi_base\t(\"4242\", \"01234\")\t\t\t\t %d\n", ft_atoi_base("4242", "01234"));
	printf("\nFT_ATOI INVALID NUMBERS\n");
	printf("ft_atoi_base\t(\"blbla42\", \"0123456789\")\t\t\t %d\n", ft_atoi_base("blbla42", "0123456789"));
	printf("\nFT_ATOI INVALID BASES\n");
	printf("ft_atoi_base\t(\"42\", \"\\0\")\t\t\t\t\t %d\n", ft_atoi_base("42", "\0"));
	printf("ft_atoi_base\t(\"42\", \"1\")\t\t\t\t\t %d\n", ft_atoi_base("42", "1"));
	printf("ft_atoi_base\t(\"42\", \"0123+\")\t\t\t\t\t %d\n", ft_atoi_base("42", "0123+"));
	printf("ft_atoi_base\t(\"42\", \"01-34\")\t\t\t\t\t %d\n", ft_atoi_base("42", "01-34"));
	printf("ft_atoi_base\t(\"42\", \" 01234\")\t\t\t\t %d\n", ft_atoi_base("42", " 01234"));
	printf("ft_atoi_base\t(\"42\", \"0123\")\t\t\t\t\t %d\n", ft_atoi_base("42", "0123"));
	//printf(BLUE"C's atoi: %d\n"GREEN, atoi(NULL));
	//printf("My Ft_atoi_base: %d\n", ft_atoi_base(NULL, "0123456789"));
	//printf("My Ft_atoi_base: %d\n", ft_atoi_base("1", NULL));
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
	begin_list = list;
	ft_list_push_front(&list, data);
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
		char 	alphabet[] = {"qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM9382764501"};
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

void	listsorttest(t_list *list)
{
	printf(GREEN"\nINITIAL LIST ORDER:\n");
	printlist(list);
	ft_list_sort(&list, ft_strcmp);
	printf("\nSORTED LIST ORDER:\n");
	printlist(list);
	printf("\n"RESET);
}

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

	ft_write(1, "\n", 1);
	bonusdependencytest();
	atoitest();
	pushfronttest("Canario", "Estepario");
	list = createalphabetlist(qwerty);
	printf(GREEN"\n\nMy List Length: %d\n"RESET, ft_list_size(list));
	listsorttest(list);
	listremoveiftest(list, "0");
	freecontent(list);
	freelist(list);
	//system("leaks a.out"); // 1 16-byte leak, definitely a struct member...
	return (0);
}