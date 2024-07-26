/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execute_pipe.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 16:16:36 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/26 22:09:59 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
			return (perror("fork"), ft_free_fd(&fd), ft_free_pid(&pid), FRKERR);
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
			// if (WIFEXITED(status) != 0) // SIGNAL HANDLING | MAYBE SOMETHING 
			// else if (WIFSIGNALED(status))
			// 	shell->exit_status += 128;
		}
		i++;
	}
	return (ft_free_fd(&fd), ft_free_pid(&pid), shell->exit_status);
}
