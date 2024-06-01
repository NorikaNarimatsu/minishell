/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:44:54 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:36 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_isdigit(int c)
{
	if ((c >= '0') & (c <= '9'))
		return (1);
	else
		return (0);
}

/*
#include <stdio.h>
int main()
{
	printf("%d\n", ft_isdigit('5'));
	printf("%d\n", ft_isdigit('a'));
	return (0);
}
*/
