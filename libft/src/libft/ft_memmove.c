/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:23:55 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:24 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*destination;
	const char	*source;

	if (!dest && !src)
		return (NULL);
	destination = (char *)dest;
	source = (const char *)src;
	if (dest < src)
		ft_memcpy(dest, src, n);
	else
	{
		while (n > 0)
		{
			destination[n - 1] = source[n - 1];
			n--;
		}
	}
	return (dest);
}

/*
#include<stdio.h>
#include<string.h>

int	main()
{
	char	buf1[] = "abcdef";
	char	buf3[] = "abcdef";
	//char	buf3[] = {'a', 'b', 'c', 'd', '\0', 'e'};
	//char	buf1[] = {'a', 'b', 'c', 'd', '\0', 'e'};


	printf("Original\n");
	printf("buf1:%s\n\n", buf1);
	memmove(&buf1[2], &buf1[0], 3);
	ft_memmove(&buf3[2], &buf3[0], 3);
	printf("YES MINE\n buf3:%s\n", buf3);
	printf("Not MINE\n buf1:%s\n", buf1);

	return (0);
}


// memcpyの方は、メモリ領域に重複があった場合の動作は保証されず、
// memmoveの方は、メモリ領域に重複があった場合でも動作は保証されます。

    // char buf1[16];
    // char buf2[16];
    // memset(buf1, '\0', 16);
    // memset(buf2, '\0', 16);

    // // メモリ領域を特定の文字で埋める
    // memset(buf1, 'b', 4);  // buf1の最初の4バイトをaにする -> bbbb
    // memset(buf1, 'a', 2);  // buf1の最初の2バイトをbにする -> aabb
    // printf("配列の要素を表示(コピー前)。\n");
    // printf("buf1:%s\n", buf1);
    // printf("buf2:%s\n", buf2);

    // // メモリを上書きする
    // memmove(buf2, buf1, 3);  // buf1の先頭3バイトをbuf2に上書きする
    // memmove(&buf1[2], &buf1[0], 3);
	// buf1の先頭3バイトをbuf1の3バイト目に上書きする -> aaaab
    // // memmove(&buf1[2], &buf1[0], 3);
	// buf1の先頭4バイトをbuf1の3バイト目に上書きする -> aaaabb

    // // 配列の内容を表示
    // printf("配列の要素を表示(コピー後)。\n");
    // printf("buf1:%s\n", buf1);
    // printf("buf2:%s\n", buf2);

	// printf("-------------------\n");
*/
