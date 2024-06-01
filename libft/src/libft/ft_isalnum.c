/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 15:18:39 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:30 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isalnum(int c)
{
	if (ft_isdigit(c) || ft_isalpha(c))
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
int main()
{
	printf("%d\n", ft_isalnum('1'));
	printf("%d\n", ft_isalnum('p'));
	printf("%d\n", ft_isalnum('@'));
	printf("%d\n", ft_isalnum('/'));
	printf("%d\n", '@');
	printf("%d\n", '1');
	return (0);
}
*/
