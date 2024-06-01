/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 19:51:25 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:02 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlcpy(char	*dst, const char	*src, size_t size)
{
	size_t	i;
	size_t	src_len;

	i = 0;
	src_len = 0;
	while (src[src_len] != '\0')
		src_len ++;
	if (size > 0)
	{
		while (i < size -1 && src[i] != '\0')
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (src_len);
}

/*
//#include <stdio.h>
//int main()
//{

//	char src[] = "coucou";
//	char dest[10];
//	printf("\nTEST 2:\n");
//	memset(dest, 'A', 10);
//	 printf("%d \n",ft_strlcpy(dest, src, 1)
== strlen(src) && dest[0] == 0 && dest[1] == 'A');
//	printf("\nTEST 3:\n");
//	memset(dest, 'A', 10);
//	 printf("%d \n",ft_strlcpy(dest, src, 2)
    //== strlen(src) && dest[0] == 'c' && dest[1] == 0  && dest[2] == 'A');
//	printf("\nTEST 5:\n");
//	memset(dest, 'A', 10);
//	 printf("%d \n",ft_strlcpy(dest, src, 6)
// == strlen(src) && !memcmp(src, dest, 5) && dest[5] == 0);
//	write(1, "\n", 1);
//	return (0);

//}

#include <stdio.h>
int main()
{
    char src[] = "Hello, world!";
    char dst1[20]; // Destination buffer for ft_strlcpy
    char dst2[20]; // Destination buffer for strlcpy
    size_t size = sizeof(dst1);

    // Use ft_strlcpy to copy the string
    size_t result1 = ft_strlcpy(dst1, src, size);

    // Use strlcpy to copy the string
    size_t result2 = strlcpy(dst2, src, size);

    // Compare the results and the destination buffers
    if (result1 == result2 && strcmp(dst1, dst2) == 0)
    {
        printf("Both functions produced the same result:\n");
        printf("Result: %zu\n", result1);
        printf("dst1: \"%s\"\n", dst1);
        printf("dst2: \"%s\"\n", dst2);
    }
    else
    {
        printf("The functions produced different results:\n");
        printf("ft_strlcpy result: %zu\n", result1);
        printf("strlcpy result: %zu\n", result2);
        printf("dst1: \"%s\"\n", dst1);
        printf("dst2: \"%s\"\n", dst2);
    }

    return 0;
}
*/
