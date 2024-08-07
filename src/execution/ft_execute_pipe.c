/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute_pipe.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 16:16:36 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/07 23:16:08 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_setup_pipes(int *fd, int num_cmnds)
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

static int	ft_init_pipes_and_pid(t_shell *shell, int **fd, pid_t **pid)
{
	*fd = ft_calloc(2 * (shell->n_cmd - 1), sizeof(int));
	if (!*fd)
		return (MALERR);
	if (ft_setup_pipes(*fd, shell->n_cmd - 1) == PIPERR)
		return (ft_free_fd(fd), PIPERR);
	*pid = ft_calloc(shell->n_cmd, sizeof(pid_t));
	if (!*pid)
		return (ft_free_fd(fd), MALERR);
	return (0);
}

static int	ft_fork_execute(t_shell *shell, t_exec *exec, int *fd, pid_t *pid)
{
	int	i;

	i = 0;
	while (exec)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (perror("fork"), FRKERR);
		else if (pid[i] == 0)
		{
			ft_ms_signal(shell, EXECUTION);
			ft_manage_redirect(shell, exec, fd, i);
			ft_execute_command(exec, shell->env, shell);
		}
		i++;
		exec = exec->pipe;
	}
	return (0);
}

int	ft_execute_pipe(t_shell *shell, t_exec *exec)
{
	t_exec	*head;
	int		*fd;
	pid_t	*pid;
	int		status;
	int		i;

	i = 0;
	head = exec;
	status = ft_init_pipes_and_pid(shell, &fd, &pid);
	if (status != 0)
		return (status);
	status = ft_fork_execute(shell, exec, fd, pid);
	exec = head;
	while (i < 2 * (shell->n_cmd - 1))
	{
		if (fd[i] != -1)
			close(fd[i]);
		i++;
	}
	ft_signal_exit_status(shell, pid);
	return (ft_free_fd(&fd), ft_free_pid(&pid), shell->exit_status);
}
