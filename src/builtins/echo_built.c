/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo_built.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 14:50:35 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/10 13:26:41 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	echo_builtin(char **args, t_shell *shell)
{
	bool	n_flag;

	(void) shell;
	if (!args[1])
		return (printf("\n"), EXIT_SUCCESS);
	n_flag = is_n_flag(args[1]);
	if (n_flag == true)
		echo_print_args(args, n_flag, 2);
	else
		echo_print_args(args, n_flag, 1);
	return (EXIT_SUCCESS);
}
