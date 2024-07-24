/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_pwd.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:49:52 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/24 20:18:55 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_builtin(t_env *env)
{
	t_env	*current;

	current = env;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			ft_putendl_fd(current->value, 1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}
