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
	char	*path;
	char	**envp;

	path = exec->word[0];
	envp = ft_env_to_array(env);
	if (is_builtin(path))
	{
		shell->exit_status = ft_execute_builtin(shell, exec, &env);
		free(envp);
		exit(shell->exit_status);
	}
	else
	{
		if (strchr(path, '/') == NULL)
			path = ft_search_path(path, env);
		ft_validate_access(path, exec->word[0], shell);
		execve(path, exec->word, envp);
		ft_putstr_fd("execve error", 2);
		free(envp);
		exit(EXIT_FAILURE);
	}
}

void	ft_handle_cmnd(t_shell *shell, t_exec *exec, int *fd, int idx)
{
	int	i;

	ft_open_io(exec);
	ft_redirect_io(exec);
	if (idx > 0)
	{
		if (dup2(fd[2 * (idx - 1)], STDIN_FILENO) < 0)
		{
			ft_putstr_fd("dup2 stdin error", 2);
			exit(EXIT_FAILURE);
		}
	}
	if (idx < shell->n_cmd - 1 && !exec->fd_outfile)
	{
		if (dup2(fd[2 * idx + 1], STDOUT_FILENO) < 0)
		{
			ft_putstr_fd("dup2 stdout error", 2);
			exit(EXIT_FAILURE);
		}
	}
	i = 0;
	while (i < 2 * (shell->n_cmd - 1))
		close(fd[i++]);
	ft_execute_command(exec, shell->env, shell);
}
