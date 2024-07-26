/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_echo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 15:46:42 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/26 16:44:53 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_n_flag_string(char *str)
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

static void	echo_print_args(char **input, int idx, bool n_flag)
{
	int	i;

	i = idx;
	if (!input[i])
	{
		if (!n_flag)
			ft_putstr_fd("\n", 1);
		return ;
	}
	while (input[i])
	{
		ft_putstr_fd(input[i], 1);
		if (input[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!n_flag)
		ft_putstr_fd("\n", 1);
}

int	ft_echo_builtin(char **input)
{
	bool	n_flag;
	int		idx;

	n_flag = false;
	idx = 1;
	if (!input[1])
	{
		write(1, "\n", 1);
		return (0);
	}
	while (input[idx] && is_n_flag_string(input[idx]))
	{
		n_flag = true;
		idx++;
	}
	echo_print_args(input, idx, n_flag);
	return (0);
}
