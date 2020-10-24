/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strfunctests.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: miki <miki@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/24 14:41:41 by miki              #+#    #+#             */
/*   Updated: 2020/10/24 16:16:43 by miki             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libasm.h"

/*
** This function tests my ft_strlen against C's strlen by passing both of them
** the same string and printing out the result. Simples. :)
**
** Behaviour with a NULL string is undefined in both strlen and ft_strlen. It
** results in a segfault in both. This strlen actually uses an x86 instruction
** called scas rather than the typical method of iterating with a counter. I use
** scas a few times in libasm to parse strings. It's a finicky instruction, but
** cool. ^_^
*/

void	teststrlen(char *string)
{
	write(1, GREEN, sizeof(GREEN));
	printf("\nMy Strlen:\nft_strlen result: %zu\n", ft_strlen(string));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strlen\nC strlen result: %zu\n", strlen(string));
	write(1, RESET, sizeof(RESET));
}

/*
** This function tests my ft_strcmp against C's strcmp by passing both of them
** the same two strings and printing out the result. Simples. :)
**
** Behaviour is undefined with NULL strings in both. (That basically means
** segfault).
*/

void	teststrcmp(char *s1, char *s2)
{
	ft_write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Strcmp:\n%d\n", ft_strcmp(s1, s2));
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strcmp:\n%d\n", strcmp(s1, s2));
	write(1, RESET, sizeof(RESET));
}

/*
** This function tests my ft_strcpy against C's strcpy by passing both of them
** the same source string and each of them a different dest string, and then
** printing out both dest strings to check the copy. The dest strings are passed
** with different data so they will be overwritten by the copy.
**
** Behaviour is undefined with NULL strings in both. (Segfault).
**
** Weirdly, both of them also segfault if I send them a string literal. o_O
** I don't quite understand why yet, but as it's not an issue with my function,
** and we can't instantiate arrays due to Norminette rules, I just use calloc.
*/

void	teststrcpy(char *mydst, char *cdst, char *src)
{
	ft_write(1, GREEN, sizeof(GREEN));
	ft_strcpy(mydst, src);
	printf("\n\nMy Strcpy:\n%s\n", mydst);
	write(1, BLUE, sizeof(BLUE));
	strcpy(cdst, src);
	printf("\nC's Strcpy:\n%s\n", cdst);
	write(1, RESET, sizeof(RESET));
}

/*
** This function tests my ft_strdup against C's strdup.
**
** We pass a source string to the function and use both ft_strdup (first) and
** strdup (second) to do a copy, print the copy and, of course, free the copy.
** If the copy fails both functions should set an ENOMEM error in errno. This
** can be tested for my function, but the only way I know to do it currently
** is modifying the strdup source code before compilation to throw the error
** so as to force it onto the error branch. I can't do that for the original
** strdup, of course (well, I mean... I COULD attempt to hack the system
** library, I guess... but I'm afraid that would be a TIG. xD).
**
** You can test the malloc failure condition by having it go onto the error
** branch in case of success, or by having it ask malloc to reserve -1 bytes.
**
** As with some other functions, there is no protection against NULL strings in
** the original strdup, so there is also no such protection in ft_strdup. The
** behaviour in that case is undefined, and it leads to a predictable segfault.
**
** If anyone knows a more elegant way to test the malloc failure condition,
** please do enlighten me!
*/

void	teststrdup(char *src)
{
	char *cpy;

	cpy = ft_strdup(src);
	ft_write(1, GREEN, sizeof(GREEN));
	printf("\n\nMy Strdup:\n");
	if (cpy)
	{
		printf("%s\n", cpy);
		free(cpy);
		cpy = NULL;
	}
	else
		perror(0);
	cpy = strdup(src);
	write(1, BLUE, sizeof(BLUE));
	printf("\nC's Strdup:\n");
	if (cpy)
	{
		printf("%s\n", cpy);
		free(cpy);
		cpy = NULL;
	}
	else
		perror(0);
	write(1, RESET, sizeof(RESET));
}
