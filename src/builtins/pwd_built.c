/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd_built.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:49:52 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/06/18 16:22:31 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(char **argv, t_shell *shell)
{
	t_env	*current;

	(void) argv;
	current = shell->env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			shell->cwd = current->value;
			return (ft_putendl_fd(shell->cwd, 1), EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_FAILURE);
}