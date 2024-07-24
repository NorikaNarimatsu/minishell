/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:42:57 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/24 15:47:34 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_exit(char *message, int exit_code)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}

void	ft_setup_pipes(int *fd, int num_cmnds)
{
	int	i;

	i = 0;
	while (i < num_cmnds)
	{
		if (pipe(fd + 2 * i) < 0)
			ft_error_exit("Pipe Error\n", EXIT_FAILURE);
		i++;
	}
}

static int	ft_execute_single(t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (ft_open_io(shell->execution) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	ft_redirect_io(shell->execution);
	if (is_builtin(shell->execution->word[0]))
		return (ft_execute_builtin(shell, shell->execution, &shell->env));
	else
	{
		pid = fork();
		if (pid < 0)
			ft_error_exit("Fork Error\n", EXIT_FAILURE);
		else if (pid == 0)
		{
			if (shell->execution->fd_infile == -1)
			{
				if (dup2(shell->saved_stdin, STDIN_FILENO) < 0)
					ft_error_exit("dup2 stdin error\n", EXIT_FAILURE);
			}
			ft_execute_command(shell->execution, shell->env, shell);
		}
		else
		{
			waitpid(pid, &status, 0);
			shell->exit_status = WEXITSTATUS(status);
		}
	}
	return (shell->exit_status);
}

int	ft_execute_pipe(t_shell *shell, t_exec *exec)
{
	t_exec	*head;
	int		*fd;
	pid_t	*pid;
	int		status;
	int		i;

	head = exec;
	i = 0;
	fd = ft_calloc(2 * (shell->n_cmd - 1), sizeof(int));
	if (!fd)
		ft_error_exit("Malloc error\n", EXIT_FAILURE);
	pid = ft_calloc(shell->n_cmd, sizeof(pid_t));
	if (!pid)
	{
		free(fd);
		ft_error_exit("Malloc error\n", EXIT_FAILURE);
	}
	ft_setup_pipes(fd, shell->n_cmd - 1);
	while (exec)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			free(fd);
			free(pid);
			ft_error_exit("Fork error\n", EXIT_FAILURE);
		}
		else if (pid[i] == 0)
			ft_handle_cmnd(shell, exec, fd, i);
		i++;
		exec = exec->pipe;
	}
	exec = head;
	i = 0;
	while (i < 2 * (shell->n_cmd - 1))
		close(fd[i++]);
	i = 0;
	while (i < shell->n_cmd)
	{
		waitpid(pid[i], &status, 0);
		if (i == shell->n_cmd - 1)
			shell->exit_status = WEXITSTATUS(status);
		i++;
	}
	return (free(fd), free(pid), shell->exit_status);
}

int	ft_interpret(t_shell *shell)
{
	int	status;

	shell->n_cmd = ft_count_command(shell->execution);
	shell->saved_stdin = dup(STDIN_FILENO);
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (!shell->execution->word[0])
		return (0);
	if (shell->n_cmd == 1)
		status = ft_execute_single(shell);
	else
		status = ft_execute_pipe(shell, shell->execution);
	ft_restore_io(shell->saved_stdin, shell->saved_stdout);
	shell->exit_status = status;
	return (status);
}
