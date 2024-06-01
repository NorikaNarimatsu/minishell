/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 16:04:49 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:05 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s != '\0')
	{
		count++;
		s++;
	}
	return (count);
}

/*

#include <stdio.h>
#include <string.h>
int main()
{
    printf("%d\n",ft_strlen("")); // Empty string should have a length of 0
    printf("%d\n",ft_strlen("Hello, World!"));  // String with 13 characters
    printf("%d\n",ft_strlen("12345"));  // Numeric string with 5 characters
    printf("%d\n",ft_strlen(" "));  // String with a single space
    printf("%d\n",ft_strlen("\n"));  // String with a newline character
    printf("%lu\n",strlen("norika"));
	return(0);
}
*/
