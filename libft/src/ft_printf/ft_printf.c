/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:33:13 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:56:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

//• %c Prints a single character.
int	ft_print_c(char c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

//• %s Prints a string (as defined by the common C convention).
int	ft_print_s(char *s)
{
	if (s == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(s, 1);
	return (ft_strlen(s));
}

//• %i Prints an integer in base 10.
//• %d Prints a decimal (base 10) number.
int	ft_print_d_i(int n)
{
	long	number;
	int		i;

	number = n;
	i = 0;
	if (number <= 0)
	{
		number = -number;
		i++;
	}
	while (number > 0)
	{
		number = number / 10;
		i++;
	}
	ft_putnbr_fd(n, 1);
	return (i);
}

int	ft_parse_and_print(va_list ap, char specifier)
{
	int	len;

	len = 0;
	if (specifier == 'c')
		len += ft_print_c(va_arg(ap, int));
	else if (specifier == 's')
		len += ft_print_s(va_arg(ap, char *));
	else if (specifier == 'd' || specifier == 'i')
		len += ft_print_d_i(va_arg(ap, int));
	else if (specifier == 'u')
		len += ft_print_u(va_arg(ap, unsigned int));
	else if (specifier == 'x')
		len += ft_print_hex(va_arg(ap, unsigned int), 0);
	else if (specifier == 'X')
		len += ft_print_hex(va_arg(ap, unsigned int), 1);
	else if (specifier == '%')
		len += ft_print_c('%');
	else if (specifier == 'p')
		len += ft_print_ptr(va_arg(ap, unsigned long));
	return (len);
}

int	ft_printf(const char *str, ...)
{
	int		len;
	va_list	ap;

	len = 0;
	va_start(ap, str);
	if (str == NULL)
		return (-1);
	while (*str)
	{
		if (*str != '%')
		{
			ft_putchar_fd(*str, 1);
			len++;
		}
		else
			len += ft_parse_and_print(ap, *(++str));
		str++;
	}
	va_end(ap);
	return (len);
}

// #include <stdio.h>
// #include <unistd.h>
// int main()
// {
// 	int test = 12345;

// 	printf("printf: %d\n", test);
// 	ft_printf("ft_printf: %d\n", test);
// 	return 0;
// }

//#include <stdio.h>
//int main(void)
//{
//	printf("%d\n", printf(NULL));
//	printf("%d", ft_printf(NULL));

//}
//	char c = 'A';
//	char *s = "hey!";
//	char *s2 = NULL;
//	int d = 12345;
//	int x = 16;
//	int X = 4095;
//	unsigned int u = 4294967295; // Maximum unsigned int value
//	void *ptr = &c;
//	void *ptr2 = NULL;
////	int printed = ft_printf("This is MY__ FUNCTION \n
//							Character: %c\nString: %s\nString2: %s
//							\nInteger: %d\nLowercase Hex: %x
//							\nUppercase Hex: %X\nPercentile: %%
//							\nU: %u\nptr: %p\nptr2: %p\n\n",
//							c, s, s2, d, x, X, u, ptr, ptr2);
////	int printed_real = printf("This is REAL FUNCTION \n
//							Character: %c\nString: %s\nString2: %s
//							\nInteger: %d\nLowercase Hex: %x
//							\nUppercase Hex: %X\nPercentile: %%
//							\nU: %u\nptr: %p\nptr2: %p\n\n",
//							c, s, s2, d, x, X, u, ptr, ptr2);

//	printf("Number of characters printed: %d\n", printed);
//	printf("Number of characters printed: %d\n", printed_real);
//	return 0;
//}
