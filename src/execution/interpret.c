/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpret.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 16:42:57 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/25 21:54:51 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_exit(char *message, int exit_code)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}

int	ft_setup_pipes(int *fd, int num_cmnds)
{
	int	i;

	i = 0;
	while (i < num_cmnds)
	{
		if (pipe(fd + 2 * i) == -1)
			return (perror("pipe"), PIPERR);
		i++;
	}
	return (0);
}

static int	ft_execute_single(t_shell *shell)
{
	pid_t	pid;
	int		status;

	if (ft_open_io(shell->execution) == 1)
		return (1);
	if (ft_redirect_io(shell->execution) == DUPERR)
		return (DUPERR);
	if (is_builtin(shell->execution->word[0]) == true)
		return (ft_execute_builtin(shell->execution, &shell->env));
	else
	{
		pid = fork();
		if (pid == -1)
			return (perror("fork"), FRKERR);
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
			// if (WIFEXITED(status) != 0)			// SIGNAL HANDLING | MAYBE SOMETHING 
			// else if (WIFSIGNALED(status))
			// 	shell->exit_status += 128;
		}
	}
	return (shell->exit_status);
}

void	ft_free_fd(int **fd)
{
	if (!fd || !*fd)
		return ;
	free(*fd);
	*fd = NULL;
}

void	ft_free_pid(pid_t **pid)
{
	if (!pid || !*pid)
		return ;
	free(*pid);
	*pid = NULL;
}

void	ft_manage_redirect(t_shell *shell, t_exec *exec, int *fd, int i)
{
	if (ft_open_io(exec) == 1)
		exit(EXIT_FAILURE);
	if (ft_redirect_io(exec) == DUPERR)
		exit(EXIT_FAILURE);
	if (ft_redirect_pipe(shell, exec, fd, i) == DUPERR)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < 2 * (shell->n_cmd - 1))
		close(fd[i++]);
}

int	ft_execute_pipe(t_shell *shell, t_exec *exec)
{
	t_exec	*head;
	int		*fd;
	pid_t	*pid;
	int		status;
	int		i;

	head = exec;
	fd = ft_calloc(2 * (shell->n_cmd - 1), sizeof(int));
	if (!fd)
		return (MALERR);
	if (ft_setup_pipes(fd, shell->n_cmd - 1) == PIPERR)
		return (ft_free_fd(&fd), PIPERR);
	pid = ft_calloc(shell->n_cmd, sizeof(pid_t));
	if (!pid)
		return (ft_free_fd(&fd), MALERR);
	i = 0;
	while (exec)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror("fork"), ft_free_fd(&fd), \
				ft_free_pid(&pid), FRKERR);
		else if (pid[i] == 0)
		{
			ft_manage_redirect(shell, exec, fd, i);
			ft_execute_command(exec, shell->env, shell);
		}
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
		{
			shell->exit_status = WEXITSTATUS(status);
			// if (WIFEXITED(status) != 0)			// SIGNAL HANDLING | MAYBE SOMETHING 
			// else if (WIFSIGNALED(status))
			// 	shell->exit_status += 128;
		}
		i++;
	}
	return (ft_free_fd(&fd), ft_free_pid(&pid), shell->exit_status);
}

int	ft_interpret(t_shell *shell)
{
	int	status;

	shell->n_cmd = ft_count_command(shell->execution);
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
		return (perror("dup stdin"), DUPERR);
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
		return (perror("dup stdout"), DUPERR);
	if (ft_ms_count_words(shell->execution->word) == 0 && shell->n_cmd == 1)
		return (shell->exit_status);
	if (shell->n_cmd == 1)
		status = ft_execute_single(shell);
	else
		status = ft_execute_pipe(shell, shell->execution);		// we are checking here
	if (ft_restore_io(shell->saved_stdin, shell->saved_stdout) == DUPERR)
		return (DUPERR);
	shell->exit_status = status;
	return (status);
}
