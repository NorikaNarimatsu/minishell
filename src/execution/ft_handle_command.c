/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_command.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 16:04:45 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 20:49:56 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to execute a command
void	ft_execute_command(t_exec *exec, t_env *env, t_shell *shell)
{
	char	*path;
	char	**envp;

	path = exec->word[0];
	envp = ft_env_to_array(env);
	if (is_builtin(path))
	{
		shell->exit_status = ft_execute_builtin(shell, exec, &env);
		exit(shell->exit_status);
	}
	else
	{
		if (strchr(path, '/') == NULL)
			path = ft_search_path(path, env);
		ft_validate_access(path, exec->word[0]);
		execve(path, exec->word, envp);
		ft_fatal_error("execve");
	}
}

// Function to handle a command in a pipeline
void	ft_handle_command(t_shell *shell, t_exec *exec, int *fd, int num_cmnd, int index, t_env *env)
{
	int	i;

	ft_open_io(exec);
	ft_redirect_io(exec);
	if (index > 0)
	{
		if (dup2(fd[2 * (index - 1)], STDIN_FILENO) < 0)
			ft_fatal_error("dup2 stdin");
	}
	if (index < num_cmnd - 1)
	{
		if (dup2(fd[2 * index + 1], STDOUT_FILENO) < 0)
			ft_fatal_error("dup2 stdout");
	}
	i = 0;
	while (i < 2 * (num_cmnd - 1))
		close(fd[i++]);
	ft_execute_command(exec, env, shell);
}

