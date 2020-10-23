/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoitests.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:49:31 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/23 22:42:51 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** This compare function call the numbers defined in atoitests.h to pass as
** arguments to my ft_atoi_base and C's atoi and prints the results.
**
** My function also needs to be provided the base 10 digits, of course, since
** it's a variable base atoi. C's atoi assumes base 10, so it only takes the
** number as an argument. Otherwise, in this, case they have equivalent
** functionality.
**
** Both will take the base 10 number string and return its value as a base 10
** int, which we print with printf. I highlight C's atoi in blue and my
** ft_atoi_base in green. Some numbers have spaces in front of the number, signs
** or symbols after the number that are not part of the base.
**
** Test 1 tests a negative number with some spaces and a tab in front of it.
** Test 2 tests a positive number with all isspace whitespaces in front of it.
** Test 3 tests a signed positive number with spaces in front of it.
** Test 4 tests a negative 0 with some isspace whitespaces in front of it.
** Test 5 tests a 0 with no spaces.
** Test 6 tests a 1 with no spaces.
** Test 7 tests INT_MIN with some non-base characters after it.
** Test 8 tests INT_MAX with some non-base characters after it.
*/

void	atoicompare(void)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\n\nFT_ATOI/ATOI COMPARE\n");
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST1, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST1));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST2, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST2));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST3, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST3));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST4, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST4));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST5, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST5));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST6, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST6));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST7, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST7));
	printf("ft_atoi_base:\t %d\n", ft_atoi_base(TEST8, "0123456789"));
	printf(BLUE"atoi:\t\t %d\n"GREEN, atoi(TEST8));
}

/*
** Test 9 tests a binary conversion with multiple signs.
** Test 10 tests a decimal conversion with multiple signs.
** Test 11 tests a hexadecimal conversion.
** Test 12 tests an octal conversion.
** Test 13 tests a quinary conversion.
*/

void	atoibaseconversions(void)
{
	printf("Base 2:\t\t %d\n", ft_atoi_base(TEST9, "01"));
	printf("Base 10:\t %d\n", ft_atoi_base(TEST10, "0123456789"));
	printf("Base 16:\t %d\n", ft_atoi_base(TEST11, "0123456789abcdef"));
	printf("Base 8:\t\t %d\n", ft_atoi_base(TEST12, "01234567"));
	printf("Base 5:\t\t %d\n", ft_atoi_base(TEST13, "01234"));
}

/*
** Test 14 tests a number with non-base characters in front of it.
*/

void	invalidnumber(void)
{
	printf("Invalid Number:\t %d\n", ft_atoi_base(TEST14, "0123456789"));
}

/*
** Test 15 tests a base with a single null character.
** Test 16 tests a base with a single non-null character.
** Test 17 tests a base with a '+' sign in it.
** Test 18 tests a base with a '-' sign in it.
** Test 19 tests a base with a ' ' (sp) in it.
** Test 20 tests a base missing a symbol ('4') from the number.
*/

void	invalidbases(void)
{
	printf("Base is \'\\0\':\t %d\n", ft_atoi_base("42", TEST15));
	printf("Base is \'1\':\t %d\n", ft_atoi_base("42", TEST16));
	printf("Base has \'+\':\t %d\n", ft_atoi_base("42", TEST17));
	printf("Base has \'-\':\t %d\n", ft_atoi_base("42", TEST18));
	printf("Base has \' \':\t %d\n", ft_atoi_base("42", TEST19));
	printf("Missing symbol:\t %d\n", ft_atoi_base("42", TEST20));
}
