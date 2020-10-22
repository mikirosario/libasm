/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoitests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:49:31 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/22 22:56:04 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** Still too big... :p
*/

void	atoicompare(void)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nFT_ATOI/ATOI COMPARE\n");
	printf("ft_atoi_base\t(\"  \\t-42\", \"0123456789\")\t\t\t %d\n",
	ft_atoi_base("  \t-42", "0123456789"));
	printf(BLUE"atoi\t\t(\"  \\t-42\")\t\t\t\t\t %d\n"GREEN, atoi("  \t-42"));
	printf("ft_atoi_base\t(\"  \\t\\n\\r\\v\\f  42\", \"0123456789\")\t\t %d\n",
	ft_atoi_base("  \t\n\r\v\f  42", "0123456789"));
	printf(BLUE"atoi\t\t(\"  \\t\\n\\r\\v\\f  42\")\t\t\t\t %d\n"GREEN,
	atoi("  \t\n\r\v\f  42"));
	printf("ft_atoi_base\t(\"    +42\", \"0123456789\")\t\t\t %d\n",
	ft_atoi_base("    +42", "0123456789"));
	printf(BLUE"atoi\t\t(\"    +42\")\t\t\t\t\t %d\n"GREEN, atoi("    +42"));
	printf("ft_atoi_base\t(\" \\n\\v\\f -0\", \"0123456789\")\t\t\t %d\n",
	ft_atoi_base(" \n\v\f -0", "0123456789"));
	printf(BLUE"atoi\t\t(\" \\n\\v\\f -0\")\t\t\t\t\t %d\n"GREEN,
	atoi(" \n\v\f -0"));
	printf("ft_atoi_base\t(\"0\", \"0123456789\")\t\t\t\t %d\n",
	ft_atoi_base("0", "0123456789"));
	printf(BLUE"atoi\t\t(\"0\")\t\t\t\t\t\t %d\n"GREEN, atoi("0"));
	printf("ft_atoi_base\t(\"1\", \"0123456789\")\t\t\t\t %d\n",
	ft_atoi_base("1", "0123456789"));
	printf(BLUE"atoi\t\t(\"1\")\t\t\t\t\t\t %d\n"GREEN, atoi("1"));
	printf("ft_atoi_base\t(\"-2147483648basurilla\", \"0123456789\")\t\t %d\n",
	ft_atoi_base("-2147483648basurilla", "0123456789"));
	printf(BLUE"atoi\t\t(\"-2147483648basurilla\")\t\t\t %d\n"GREEN,
	atoi("-2147483648basurilla"));
	printf("ft_atoi_base\t(\"-2147483647basurilla\", \"0123456789\")\t\t %d\n",
	ft_atoi_base("2147483647basurilla", "0123456789"));
	printf(BLUE"atoi\t\t(\"-2147483647basurilla\")\t\t\t %d\n"GREEN,
	atoi("2147483647basurilla"));
}