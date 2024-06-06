/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:50:35 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/06 14:37:07 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

bool	is_n_flag(char *arg)
{
	int		i;

	if (arg[0] != '-')
		return (false);
	i = 1;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		return (true);
	return (false);
}

void	echo_print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putchar_fd(' ', 1);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', 1);
		i++;
	}
}

int	echo_builtin(char **args, t_data *data)
{
	bool	n_flag;

	if (!args[2])
		return (printf("\n"), EXIT_SUCCESS);
	(void) data;
	n_flag = is_n_flag(args[2]);
	if (n_flag == true)
		echo_print_args(args, n_flag, 3);
	else
		echo_print_args(args, n_flag, 2);
	return (EXIT_SUCCESS);
}
