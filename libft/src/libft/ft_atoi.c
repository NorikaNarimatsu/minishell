/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:54:36 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:23 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_atoi(const char	*nptr)
{
	int	num;
	int	sign;
	int	final;

	num = 0;
	sign = 1;
	while ((*nptr == ' ') || ((*nptr >= '\t') && (*nptr <= '\r' )))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	final = sign * num;
	return (final);
}

//#include <stdio.h>
//int main()
//{
//    printf("%d \n",ft_atoi("-+42") == 0);
//	printf("%d \n",atoi("+1"));
//}

/*
#include <stdio.h>
#include <stdlib.h> // for comparison with the standard atoi function

int main() {
    // Test cases
    const char *str1 = "12345";
    const char *str2 = "-678";
    const char *str3 = "0";
    const char *str4 = "  42 with spaces ";
    const char *str5 = "  -9876 with spaces ";
    const char *str6 = "abc123"; // Non-numeric characters

    // Test your atoi function
    int result1 = ft_atoi(str1);
    int result2 = ft_atoi(str2);
    int result3 = ft_atoi(str3);
    int result4 = ft_atoi(str4);
    int result5 = ft_atoi(str5);
    int result6 = ft_atoi(str6);
    // This should return 0 as atoi stops at non-numeric characters

    // Test the standard atoi function for comparison
    int expected1 = atoi(str1);
    int expected2 = atoi(str2);
    int expected3 = atoi(str3);
    int expected4 = atoi(str4);
    int expected5 = atoi(str5);
    int expected6 = atoi(str6);

    printf("Test results:\n");
    printf("str1: %d (expected: %d)\n", result1, expected1);
    printf("str2: %d (expected: %d)\n", result2, expected2);
    printf("str3: %d (expected: %d)\n", result3, expected3);
    printf("str4: %d (expected: %d)\n", result4, expected4);
    printf("str5: %d (expected: %d)\n", result5, expected5);
    printf("str6: %d (expected: %d)\n", result6, expected6);

    return 0;
}
*/
