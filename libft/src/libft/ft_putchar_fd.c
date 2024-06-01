/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 14:52:02 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:31 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

/*
int main() {
    int file_descriptor = 1; // 1 represents standard
	output (stdout)

    char character = 'A'; //

    // Call your ft_putchar_fd function to write the character to stdout
    ft_putchar_fd(character, file_descriptor);

    return 0;
}
*/
