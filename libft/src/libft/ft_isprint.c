/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:53:03 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:45 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isprint(int c)
{
	if ((c >= 32) & (c <= 126))
		return (1);
	else
		return (0);
}

/*
#include <ctype.h>
#include <stdio.h>
int main()
{
	printf("%d\n", ft_isprint(' '));
	printf("%d\n", ft_isprint('S'));
	printf("%d\n",ft_isprint(127));
    printf("%d\n",ft_isprint(0));    // 0 is an ASCII character
	return (0);
}
*/
