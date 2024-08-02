/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_single.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 16:17:33 by mdraper           #+#    #+#             */
/*   Updated: 2024/08/02 19:46:58 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execute_single(t_shell *shell)
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
		ft_ms_signal(shell, EXECUTION);
		pid = fork();
		if (pid == -1)
			return (perror("fork"), FRKERR);
		else if (pid == 0)
		{
			if (shell->execution->fd_infile == -1
				&& shell->execution->fd_heredoc == -1)
			{
				if (dup2(shell->saved_stdin, STDIN_FILENO) < 0)
					ft_error_exit("dup2 stdin error\n", EXIT_FAILURE);
			}
			ft_execute_command(shell->execution, shell->env, shell);
		}
		else
		{
			waitpid(pid, &status, 0);
			if (WIFEXITED(status) != 0)
				shell->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				shell->exit_status = WTERMSIG(status) + 128;
		}
	}
	return (shell->exit_status);
}
