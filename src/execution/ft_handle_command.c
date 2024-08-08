/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_cmnd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:04:45 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/20 19:52:31 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_command(t_exec *exec, t_env *env, t_shell *shell)
{
	char		*path;
	char		**envp;

	if (is_builtin(exec->word[0]) == true)
	{
		shell->exit_status = ft_execute_builtin(exec, &env, shell);
		if (shell->exit_status < 0)
			exit(EXIT_FAILURE);
		exit(shell->exit_status);
	}
	else
	{
		path = ft_path_error(exec, env, exec->word[0]);
		envp = ft_env_to_array(env);
		if (!envp)
			exit(EXIT_FAILURE);
		if (execve(path, exec->word, envp) == -1)
		{
			ft_free_array(&envp);
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}
