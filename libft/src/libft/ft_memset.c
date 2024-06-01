/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:28:34 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:28 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memset(void	*s, int c, size_t n)
{
	unsigned char	*s_char;

	s_char = (unsigned char *)s;
	while (n > 0)
	{
		*s_char = c;
		s_char++;
		n--;
	}
	return (s);
}

/*
#include <stdio.h>
#include <string.h>
#include <assert.h>
void test_ft_memset()
{
    char buf1[10];
    char buf2[10];

    // Initialize both buffers with '\0'
    ft_memset(buf1, '\0', 10);
    ft_memset(buf2, '\0', 10);

    printf("After Initialization:\n");
    printf("buf1: %s\n", buf1);
    printf("buf2: %s\n", buf2);

    // Set 'n' characters in buf1 to 'o' and 'k' characters in buf2 to 'k'
    ft_memset(buf1, 'o', 8);
    ft_memset(buf2, 'k', 3);

    printf("After changing:\n");
    printf("buf1: %s\n", buf1);
    printf("buf2: %s\n", buf2);

    // Add assertions to check the results if needed
    assert(strcmp(buf1, "oooooooo") == 0);
    assert(strcmp(buf2, "kkk") == 0);

    printf("All test cases passed!\n");
}

int main()
{
    test_ft_memset();
    return 0;
}

*/

/*
#define BUF_SIZE 16
int main ()
{
	char buf1[BUF_SIZE];
	char buf2[BUF_SIZE];

	memset(buf1, '\0', BUF_SIZE);
	memset(buf2, '\0', BUF_SIZE);

	printf("After Initialization:\n");
	printf("buf1:%s\n", buf1);
	printf("buf2:%s\n", buf2);

	//fill the letters
	printf("After change:\n");

	memset(buf1, 'a', 4);
	memset(buf1, 'b', 2);
	memset(buf2, 'c', 3);

	printf("buf1:%s\n", buf1);
	printf("buf2:%s\n", buf2);

	return (0);
}
*/
