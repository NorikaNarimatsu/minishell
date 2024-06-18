/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_built.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:21:39 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/06/18 16:22:59 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(char **argv, t_shell *shell)
{
	t_env	*current;

	if (argv && argv[2])
		return (-1);
	if (!shell->env)
		return (EXIT_FAILURE);
	current = shell->env;
	while (current)
	{
		ft_putendl_fd(current->env, 1);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
