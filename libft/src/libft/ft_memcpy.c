/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:20:01 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:21 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*destination;
	char	*source;

	i = 0;
	if (!dest && !src)
		return (NULL);
	destination = (char *)dest;
	source = (char *)src;
	while (i < n)
	{
		destination[i] = source[i];
		i++;
	}
	return (destination);
}

/*
#include <stdio.h>
#include <string.h>

int main(void)
{
	unsigned char mem1[]  = {0x12, 0x34, 0x56, 0x78};		//	コピー元
	unsigned char mem2[5] = {0xff, 0xff, 0xff, 0xff, 0xff};	//	コピー先
	printf("\nmem1[]:%x %x %x %x", mem1[0], mem1[1], mem1[2], mem1[3]);
	printf("\nmem2[]:%x %x %x %x %x", mem2[0],mem2[1],mem2[2],mem2[3],mem2[4]);
	memcpy(mem2, mem1, sizeof(mem1));
	printf("\nmem1[]:%x %x %x %x", mem1[0], mem1[1], mem1[2], mem1[3]);
	printf("\nmem2[]:%x %x %x %x %x", mem2[0],mem2[1],mem2[2],mem2[3],mem2[4]);
	printf("\n--------------------");
	unsigned char mem3[]  = {0x12, 0x34, 0x56, 0x78};		//	コピー元
	unsigned char mem4[5] = {0xff, 0xff, 0xff, 0xff, 0xff};	//	コピー先
	printf("\nmem3[]:%x %x %x %x", mem3[0], mem3[1], mem3[2], mem3[3]);
	printf("\nmem4[]:%x %x %x %x %x", mem4[0],mem4[1],mem4[2],mem4[3],mem4[4]);
	ft_memcpy(mem4, mem3, sizeof(mem3));
	printf("\nmem3[]:%x %x %x %x", mem3[0], mem3[1], mem3[2], mem3[3]);
	printf("\nmem4[]:%x %x %x %x %x", mem4[0],mem4[1],mem4[2],mem4[3],mem4[4]);
	return (0);
}
*/
//memcpy関数とstrcpy関数との違いは、引数３としてコピーするバイト数が必要となることです。
//文字列はヌル文字で終わるルールがあるため、strcpy関数側でコピーサイズを算出できます。
//しかし、メモリには終端記号がないため、
// memcpy関数ではコピーしたいサイズを呼び出す側が与えないといけないのです。
