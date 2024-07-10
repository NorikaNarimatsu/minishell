/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:49:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 13:42:43 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(char **input, t_shell *shell)
{
	t_env	*current;

	(void) input;
	current = shell->env;
	while (current)
	{
		if (strcmp(current->key, "PWD") == 0)
		{
			shell->cwd = current->value;
			return (ft_putendl_fd(shell->cwd, 1), EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_FAILURE);
}
