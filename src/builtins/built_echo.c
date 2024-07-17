/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:46:42 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 14:12:42 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_n_flag_string(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

void	echo_print_args(char **input, int idx, bool n_flag)
{
	int	i;

	i = idx;
	if (!input[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (input[i])
	{
		ft_putstr_fd(input[i], 1);
		if (input[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}

int	ft_echo_builtin(char **input)
{
	bool	n_flag;
	int		idx;

	n_flag = false;
	idx = 1;
	if (!input[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	while (input[idx] && is_n_flag_string(input[idx]))
	{
		n_flag = true;
		idx++;
	}
	echo_print_args(input, idx, n_flag);
	return (EXIT_SUCCESS);
}
