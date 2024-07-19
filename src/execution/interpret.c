/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:42:57 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 19:34:22 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to execute a single command
static int	ft_execute_single(t_shell *shell)
{
	pid_t	pid;
	int		status;
	char	*command;
	int		exit_status;

	ft_open_io(shell->execution);
	command = shell->execution->word[0];
	if (is_builtin(command))
	{
		ft_redirect_io(shell->execution);
		exit_status = ft_execute_builtin(shell, shell->execution, &shell->env);
		return (exit_status);
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			ft_redirect_io(shell->execution);
			ft_execute_command(shell->execution, shell->env, shell);
		}
		else
		{
			waitpid(pid, &status, 0);
			exit_status = WEXITSTATUS(status);
			return (exit_status);
		}
	}
	return (0);
}

void	ft_setup_pipes(int *fd, int num_cmnds)
{
	int	i;

	i = 0;
	while (i < num_cmnds)
	{
		if (pipe(fd + 2 * i) < 0)
			ft_fatal_error("pipe");
		i++;
	}
}

// Function to execute multiple commands in a pipeline
int	ft_execute_pipe(t_shell *shell, t_exec *exec, t_env *env, int num_cmnd)
{
	t_exec	*head;
	int		*fd;
	int		index;
	pid_t	pid;
	int		status;
	int		i;
	int		last_status;

	head = exec;
	index = 0;
	fd = ft_calloc(2 * (num_cmnd - 1), sizeof(int));
	if (!fd)
		ft_fatal_error("malloc");
	ft_setup_pipes(fd, num_cmnd - 1);
	while (exec)
	{
		pid = fork();
		if (pid < 0)
			ft_fatal_error("fork");
		else if (pid == 0)
			ft_handle_command(shell, exec, fd, num_cmnd, index, env);
		index++;
		exec = exec->pipe;
	}
	exec = head;
	i = 0;
	while (i < 2 * (num_cmnd - 1))
		close(fd[i++]);
	i = 0;
	while (i++ < num_cmnd)
		wait(&status);
	last_status = WEXITSTATUS(status);
	free(fd);
	return (last_status);
}

// Main interpret function
int	ft_interpret(t_shell *shell)
{
	int	num_cmnd;
	int	saved_stdin;
	int	saved_stdout;

	num_cmnd = ft_count_command(shell->execution);
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (!shell->execution->word[0])
		return (0);
	if (num_cmnd == 1)
		shell->exit_status = ft_execute_single(shell);
	else
		shell->exit_status = ft_execute_pipe(shell, shell->execution, shell->env, num_cmnd);
	ft_restore_io(saved_stdin, saved_stdout);
	return (0);
}
