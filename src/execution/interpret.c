/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:42:57 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/20 21:12:11 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static int	ft_execute_single(t_shell *shell)
{
	pid_t	pid;
	int		status;

	ft_open_io(shell->execution);
	ft_redirect_io(shell->execution);
	if (is_builtin(shell->execution->word[0]))
		return (ft_execute_builtin(shell, shell->execution, &shell->env));
	else
	{
		pid = fork();
		if (pid < 0)
		{
			ft_putstr_fd("Fork Error\n", 2);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			ft_execute_command(shell->execution, shell->env, shell);
		else
		{
			waitpid(pid, &status, 0);
			shell->exit_status = WEXITSTATUS(status);
		}
	}
	return (shell->exit_status);
}

void	ft_setup_pipes(int *fd, int num_cmnds)
{
	int	i;

	i = 0;
	while (i < num_cmnds)
	{
		if (pipe(fd + 2 * i) < 0)
		{
			ft_putstr_fd("Pipe Error\n", 2);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	ft_execute_pipe(t_shell *shell, t_exec *exec)
{
	t_exec	*head;
	int		*fd;
	pid_t	pid;
	int		status;
	int		i;

	head = exec;
	i = 0;
	fd = ft_calloc(2 * (shell->n_cmd - 1), sizeof(int));
	if (!fd)
	{
		ft_putstr_fd("Malloc Error\n", 2);
		exit(EXIT_FAILURE);
	}
	ft_setup_pipes(fd, shell->n_cmd - 1);
	while (exec)
	{
		pid = fork();
		if (pid < 0)
		{
			free(fd);
			ft_putstr_fd("Fork Error\n", 2);
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
			ft_handle_cmnd(shell, exec, fd, i);
		i++;
		exec = exec->pipe;
	}
	exec = head;
	i = 0;
	while (i < 2 * (shell->n_cmd - 1))
		close(fd[i++]);
	i = 0;
	while (i++ < shell->n_cmd)
		wait(&status);
	free(fd);
	shell->exit_status = WEXITSTATUS(status);
	return (shell->exit_status);
}

int	ft_interpret(t_shell *shell)
{
	int	saved_stdin;
	int	saved_stdout;

	shell->n_cmd = ft_count_command(shell->execution);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!shell->execution->word[0])
		return (0);
	if (shell->n_cmd == 1)
		shell->exit_status = ft_execute_single(shell);
	else
		shell->exit_status = ft_execute_pipe(shell, shell->execution);
	ft_restore_io(saved_stdin, saved_stdout);
	return (0);
}
