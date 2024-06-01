/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_sub.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 13:49:18 by nnarimat          #+#    #+#             */
/*   Updated: 2024/05/06 20:49:38 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//• %u Prints an unsigned decimal (base 10) number.
int	ft_print_u(unsigned int nb)
{
	char	numstr[12];
	int		count;
	int		i;

	count = 0;
	if (nb == 0)
	{
		ft_putchar_fd('0', 1);
		return (1);
	}
	while (nb > 0)
	{
		numstr[count] = '0' + (nb % 10);
		nb /= 10;
		count++;
	}
	i = count;
	while (i > 0)
	{
		i--;
		ft_putchar_fd(numstr[i], 1);
	}
	return (count);
}

//• %x Prints a number in hexadecimal (base 16) lowercase format.
//• %X Prints a number in hexadecimal (base 16) uppercase format.

int	ft_print_hex(unsigned int n, int uppercase)
{
	char	res[21];
	int		i;
	int		j;

	i = 0;
	if (n == 0)
		res[i++] = '0';
	while (n > 0)
	{
		if (n % 16 >= 10)
		{
			if (uppercase == 1)
				res[i++] = 'A' + (n % 16) - 10;
			else
				res[i++] = 'a' + (n % 16) - 10;
		}
		else
			res[i++] = n % 16 + '0';
		n /= 16;
	}
	j = i;
	while (i--)
		ft_putchar_fd(res[i], 1);
	return (j);
}

int	ft_recursive_print_ptr(unsigned long value, int len)
{
	char	hex_digit;
	int		digit;

	if (value > 0)
	{
		digit = value % 16;
		if (digit < 10)
		{
			hex_digit = '0' + digit;
		}
		else
		{
			hex_digit = 'a' + (digit - 10);
		}
		len += ft_recursive_print_ptr(value / 16, 1);
		ft_putchar_fd(hex_digit, 1);
	}
	return (len);
}

int	ft_print_ptr(unsigned long address)
{
	int	len;

	if (address == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	ft_putstr_fd("0x", 1);
	len = ft_recursive_print_ptr(address, 2);
	return (len);
}
