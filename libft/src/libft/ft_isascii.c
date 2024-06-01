/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:32:56 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:34 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isascii(int c)
{
	if ((c >= 0) & (c <= 127))
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>
// Codes 0 through 31 and 127 (decimal) are unprintable control characters.
// Code 32 (decimal) is a nonprinting spacing character.
// Codes 33 through 126 (decimal) are printable graphic characters.
int main()
{
	printf("%d\n", ft_isascii(' '));
	printf("%d\n", ft_isascii('S'));
	printf("%d\n",ft_isascii(127));  // 128 is not an ASCII character
    printf("%d\n",ft_isascii(-1));   // -1 is not an ASCII character
    printf("%d\n",ft_isascii(0));    // 0 is an ASCII character
	printf("%c\n", '0');
	printf("%d\n", 2);
	return (0);
}
*/
