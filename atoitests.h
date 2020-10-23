/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoitests.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrosario <mrosario@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 22:49:31 by mrosario          #+#    #+#             */
/*   Updated: 2020/10/23 22:36:56 by mrosario         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ATOITESTS_H
# define ATOITESTS_H

/*
** FT_ATOI/ATOI COMPARE TESTS
*/

# define TEST1			"  \t-42"
# define TEST2			"  \t\n\r\v\f  42"
# define TEST3			"    +42"
# define TEST4			" \n\v\f -0"
# define TEST5			"0"
# define TEST6			"1"
# define TEST7			"-2147483648basurilla"
# define TEST8			"2147483647basurilla"

/*
** BASE CONVERSION TESTS
*/

# define TEST9			"--++-+11010100010101basurilla"
# define TEST10			"--++-+-2147483648basurilla"
# define TEST11			"ff"
# define TEST12			"1411"
# define TEST13			"4242"

/*
** INVALID NUMBER TEST
*/

# define TEST14			"blbla42"

/*
** INVALID BASE TESTS
*/

# define TEST15			"\0"
# define TEST16			"1"
# define TEST17			"01234+"
# define TEST18			"012-34"
# define TEST19			" 01234"
# define TEST20			"0123"

#endif
