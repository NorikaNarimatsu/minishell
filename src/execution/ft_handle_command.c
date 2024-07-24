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
	struct stat	statbuf;

	path = exec->word[0];
	envp = ft_env_to_array(env);
	if (is_builtin(path))
	{
		shell->exit_status = ft_execute_builtin(exec, &env);
		free(envp);
		exit(shell->exit_status);
	}
	else
	{
		if (ft_strchr(path, '/') == NULL)
			path = ft_search_path(path, env);
		if (stat(path, &statbuf) == 0)
		{
			if (S_ISDIR(statbuf.st_mode))
				ft_error_exit(" Is a directory\n", 126);
			else if (access(path, X_OK) != 0)
				ft_error_exit(" Permission denied\n", 126);
		}
		else
		{
			if (ft_strchr(exec->word[0], '/') == NULL)
				ft_error_exit(" command not found\n", 127);
			else
				ft_error_exit(" No such file or directory\n", 127);
		}
		if (execve(path, exec->word, envp) == -1)
		{
			free(envp);
			ft_error_exit("execve error\n", EXIT_FAILURE);
		}
	}
}

void	ft_handle_cmnd(t_shell *shell, t_exec *exec, int *fd, int idx)
{
	int	i;

	if (ft_open_io(exec) == EXIT_FAILURE)
		exit(EXIT_FAILURE);
	ft_redirect_io(exec);
	if (idx > 0 && !exec->infile)
	{
		if (dup2(fd[2 * (idx - 1)], STDIN_FILENO) < 0)
			ft_error_exit("dup2 stdin error\n", EXIT_FAILURE);
	}
	if (idx < shell->n_cmd - 1 && !exec->outfile)
	{
		if (dup2(fd[2 * idx + 1], STDOUT_FILENO) < 0)
			ft_error_exit("dup2 stdout error\n", EXIT_FAILURE);
	}
	if (exec->fd_infile == -1 && idx == 0)
	{
		if (dup2(shell->saved_stdin, STDIN_FILENO) < 0)
			ft_error_exit("dup2 stdin error\n", EXIT_FAILURE);
	}
	i = 0;
	while (i < 2 * (shell->n_cmd - 1))
		close(fd[i++]);
	ft_execute_command(exec, shell->env, shell);
}
