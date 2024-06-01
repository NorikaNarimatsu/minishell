/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 13:07:47 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:15 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memchr(const void	*s, int c, size_t n)
{
	unsigned char	*s_cast;

	s_cast = (unsigned char *) s;
	while (n > 0)
	{
		if (*s_cast == (unsigned char)c)
			return (s_cast);
		s_cast ++;
		n --;
	}
	return (NULL);
}

/*
#include <stdio.h>
#include <string.h>
int	main()
{
	char str[] = "abcdef\0ghij";
	char *p;

	p = ft_memchr(str, 'h', 12);
	printf("検索文字は文字列の%ld番目\n",p - str);
	return (0);
}
// buf の先頭から n 文字分検索して、文字 ch がある位置を返却します。
// buf を単なるメモリブロックとして検索するため、途中に空文字('\0')を含んでいても検索を続けます。
*/
