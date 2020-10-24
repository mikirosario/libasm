/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auxfunctests_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 12:38:34 by miki              #+#    #+#             */
/*   Updated: 2020/10/24 16:42:44 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm_bonus.h"

/*
** This function tests my ft_isspace against C's isspace for all whitespaces.
** Then it tests it against C's isspace for a non-whitespace.
**
** There are 6 whitespaces: \t, \n, \v, \f, \r, ' '.
**
** Note that C's isspace is weird and returns precisely 8192 when it finds any
** space. xD I'd love to hear the explanation behind that decision. xD My
** isspace hasn't yet lost its sanity, so it just returns 1 whenever it finds
** any space. That's fine for these purposes (same functionality) as the only
** test is for a non-zero value. Both return 0 if no space is found.
*/

void	isspacetest(void)
{
	printf(GREEN"My Isspace:\t %d\n", ft_isspace('\t'));
	printf(BLUE"C's Isspace:\t %d\n", isspace('\t'));
	printf(GREEN"My Isspace:\t %d\n", ft_isspace('\n'));
	printf(BLUE"C's Isspace:\t %d\n", isspace('\n'));
	printf(GREEN"My Isspace:\t %d\n", ft_isspace('\v'));
	printf(BLUE"C's Isspace:\t %d\n", isspace('\v'));
	printf(GREEN"My Isspace:\t %d\n", ft_isspace('\f'));
	printf(BLUE"C's Isspace:\t %d\n", isspace('\f'));
	printf(GREEN"My Isspace:\t %d\n", ft_isspace('\r'));
	printf(BLUE"C's Isspace:\t %d\n", isspace('\r'));
	printf(GREEN"My Isspace:\t %d\n", ft_isspace(' '));
	printf(BLUE"C's Isspace:\t %d\n", isspace(' '));
	printf(GREEN"My Isspace:\t %d\n", ft_isspace('p'));
	printf(BLUE"C's Isspace:\t %d\n", isspace('p'));
}

/*
** This function tests my ft_strchr against C's strchr for six different cases.
**
** Case 1: Match in the first character in the string.
** Case 2: Match in the second character in the string.
** Case 3: Match in the penultimate character in the string.
** Case 4: Match in the last character in the string.
** Case 5: Match in the null character in the string.
** Case 6: No match in the string.
**
** Note that printf should be tolerant of being passed a null string pointer and
** behave by printing (null), but my Linux compiler is not. ;) It thinks it's
** pretty clever and seems to detect that this will happen and throws an error
** over it with -Werror enabled. Hence, when running this on Linux, instead of
** sending the null to printf as a string type, I send it as a pointer address
** type, so it prints (nil) and the Linux compiler quits bothering me. ;) So
** that's why I have an OS condition there. (Must remove for evaluation,
** Norminette doesn't like it).
*/

void	strchrtest(void)
{
	printf(GREEN"My Strchr:\t %s\n", ft_strchr("find", 'f'));
	printf(BLUE"C's Strchr:\t %s\n", strchr("find", 'f'));
	printf(GREEN"My Strchr:\t %s\n", ft_strchr("find", 'i'));
	printf(BLUE"C's Strchr:\t %s\n", strchr("find", 'i'));
	printf(GREEN"My Strchr:\t %s\n", ft_strchr("find", 'n'));
	printf(BLUE"C's Strchr:\t %s\n", strchr("find", 'n'));
	printf(GREEN"My Strchr:\t %s\n", ft_strchr("find", 'd'));
	printf(BLUE"C's Strchr:\t %s\n", strchr("find", 'd'));
	printf(GREEN"My Strchr:\t %s\n", ft_strchr("find", '\0'));
	printf(BLUE"C's Strchr:\t %s\n", strchr("find", '\0'));
	printf(GREEN"My Strchr:\t %s\n", ft_strchr("find", 'p'));
#ifdef __APPLE__
	printf(BLUE"C's Strchr:\t %s \n", strchr("find", 'p'));
#else
	printf(BLUE"C's Strchr:\t %p \n", strchr("find", 'p'));
#endif
}

/*
** This function simply tests the auxiliary functions that the bonus functions
** will depend on to work properly. These are ft_isspace and ft_strchr, which
** are compared against isspace and strchr, respectively. These aren't bonus
** functions themselves, but the bonus functions do depend on them, so if you
** can break them, you can probably break one or more of my bonus functions. :)
**
** Don't be shy! If I have bugs, I deserve it! xD
*/

void	auxfunctests(void)
{
	printf("\nAUXILIARY FUNCTION TESTS\n");
	isspacetest();
	strchrtest();
	write(1, RESET, sizeof(RESET));
}
