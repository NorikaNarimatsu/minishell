/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:47:05 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:33 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}

//#include <stdio.h>
//#include <ctype.h>
//int	main()
//{
//	printf("answer: %c \n", ft_toupper('m'));
//	printf("answer: %c \n", toupper('m'));
//	printf("answer: %c \n", ft_toupper('1'));
//	printf("answer: %c \n", toupper('1'));
//	printf("answer: %c \n", ft_toupper('M'));
//	printf("answer: %c \n", toupper('M'));

//	return (0);
//}
