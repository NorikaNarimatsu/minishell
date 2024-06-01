/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:24:55 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:19 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_memcmp(const void	*s1, const void	*s2, size_t n)
{
	unsigned char	*s1_cast;
	unsigned char	*s2_cast;

	s1_cast = (unsigned char *) s1;
	s2_cast = (unsigned char *) s2;
	while (n > 0)
	{
		if (*s1_cast != *s2_cast)
			return (*s1_cast - *s2_cast);
		s1_cast ++;
		s2_cast ++;
		n --;
	}
	return (0);
}

/*
#include <stdio.h>
#include <string.h> // Include the string.h header for the memcmp function

int main()
{
	char str1[] = "Hello, world!";
	char str2[] = "Hello, earth!";
	size_t n = 8; // Number of bytes to compare

	int result_ft = ft_memcmp(str1, str2, n);
	int result_std = memcmp(str1, str2, n);

	if (result_ft == 0) {
		printf("ft_memcmp: The first %zu bytes are equal.\n", n);
	} else {
		printf("ft_memcmp: The first %zu bytes are not equal.
		with result_std %d\n", n, result_ft);
	}
	if (result_std == 0) {
		printf("memcmp: The first %zu bytes are equal.\n", n);
	} else {
		printf("memcmp: The first %zu bytes are not equal.
		with result_std %d\n", n, result_std);
	}

	return 0;
}
*/
