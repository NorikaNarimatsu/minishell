/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 11:42:19 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:15 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strnstr(const char	*big, const char	*little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[i] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while ((big[i + j] == little[j]) && (i + j) < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}

/*
#include <stddef.h>
#include <string.h>
#include <stdio.h>


int main()
{
	const char	*big = "1234567890";
	const char	*little = "234";
	size_t		len;

	len = 3;
	char	*result_ft = ft_strnstr(big, little, len);

	if (result_ft != NULL)
		printf("ft_strnstr result: %s\n",  result_ft);
	else
		printf("ft_strnstr result: Substring not
		//found within the specified length.\n");

	return (0);
}
*/
