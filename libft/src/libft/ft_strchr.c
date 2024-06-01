/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:07:15 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:47 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	if ((unsigned char)c == '\0')
		return ((char *)s + ft_strlen(s));
	while (*s != '\0')
	{
		if ((unsigned char)*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	return (0);
}

//#include <stdio.h>

//int main(void)
//{
//	char s[] = "tripouille";

//	/* 1 */ printf("%p \n", ft_strchr(s, '\0') );
//	/* 2 */ printf("%d \n", ft_strchr(s, 'l') == s + 7);
//	/* 3 */ printf("%d \n", ft_strchr(s, 'z') == 0);
//	/* 4 */ printf("%d \n", ft_strchr(s, 0) == s + strlen(s));
//	/* 5 */ printf("%d \n", ft_strchr(s, '\200' ) == s);
//	/* 6 */ printf("%p \n", strchr(s, '\0' ));

//	write(1, "\n", 1);
//	return (0);
//}

//#include <string.h>
//#include <stdio.h>
//#include <stdbool.h> // for the bool data type

//// Define a function to compare two strings and print the result
//void check(char *result, char *expected) {
//    if (result == expected) {
//        printf("PASS: %s == %s\n", result, expected);
//    } else {
//        printf("FAIL: %s != %s\n", result, expected);
//    }
//}

//char *ft_strchr(const char *s, int c);

//int main() {
//    // Test ft_strchr with a string containing the character
//    const char *str1 = "Hello, World!";
//    char *result1 = ft_strchr(str1, 'o');
//    char *expected1 = strchr(str1, 'o');
//    check(result1, expected1);

//    // Test ft_strchr with a string not containing the character
//    const char *str2 = "This is a test";
//    char *result2 = ft_strchr(str2, 'x');
//    char *expected2 = strchr(str2, 'x');
//    check(result2, expected2);

//    // Test ft_strchr with an empty string
//    const char *str3 = "";
//    char *result3 = ft_strchr(str3, 'a');
//    char *expected3 = strchr(str3, 'a');
//    check(result3, expected3);

//    return 0;
//}
//*/
