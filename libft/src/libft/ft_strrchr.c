/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:18:56 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:19 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)(s + i));
		i--;
	}
	return (NULL);
}

/*

#include <string.h>
#include <stdio.h>
#include <stdbool.h> // for the bool data type

// Define a function to compare two strings and print the result
void check(char *result, char *expected) {
    if (result == expected) {
        printf("PASS: %s == %s\n", result, expected);
    } else {
        printf("FAIL: %s != %s\n", result, expected);
    }
}

int main() {
    // Test ft_strchr with a string containing the character
    const char *str1 = "Hello, World! Waa";
    char *result1 = ft_strrchr(str1, 'W');
    char *expected1 = strrchr(str1, 'W');
    check(result1, expected1);

    const char *str2 = "This is a test";
    char *result2 = ft_strrchr(str2, 'a');
    char *expected2 = strrchr(str2, 'a');
    check(result2, expected2);

    // Test ft_strchr with an empty string
    const char *str3 = "";
    char *result3 = ft_strrchr(str3, 'l');
    char *expected3 = strrchr(str3, 'l');
    check(result3, expected3);

    return 0;
}
*/
