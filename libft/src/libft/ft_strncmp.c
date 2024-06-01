/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:34:53 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:11 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n > i && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (n == i)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

//#include <stdio.h>
//int main()
//{

//	/* 1 */ printf("%d \n", ft_strncmp("\200", "a", 1));
//	///* 1 */ printf("%d \n", ft_strncmp("Tripouille", "Tripouille", 42) == 0);
//	///* 1 */ printf("%d \n", ft_strncmp("", "", 1) == 0);
//	///* 1 */ printf("%d \n", strncmp("", "", 42) == 0);
//	///* 1 */ printf("%d \n", strncmp("Tripouille", "Tripouille", 42) == 0);
//	///* 1 */ printf("%d \n", strncmp("", "", 1) == 0);

//}
//
/*
#include <stdio.h>
#include <string.h>

int main() {
    const char *str1 = "AHello, World!";
    const char *str2 = "BHello, Earth!";
    size_t n = 1; // Number of characters to compare

	//printf("%c\n", str1[11]);
    // Compare using the standard strncmp
    int result1 = strncmp(str1, str2, n);

    // Compare using your ft_strncmp
    int result2 = ft_strncmp(str1, str2, n);

    printf("Using standard strncmp:\n");
    printf("Comparison result for first %zu characters: %d\n", n, result1);

    printf("\nUsing ft_strncmp:\n");
    printf("Comparison result for first %zu characters: %d\n", n, result2);

    return 0;
}
*/
