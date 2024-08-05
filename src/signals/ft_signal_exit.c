/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signal_exit.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 22:21:24 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/05 22:22:51 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal_exit_status(t_shell *shell, pid_t	*pid)
{
	int	i;
	int	exit_status;
	int	signal_recieved;

	i = 0;
	signal_recieved = 0;
	while (i < shell->n_cmd)
	{
		ft_ms_signal(shell, IGNORE);
		waitpid(pid[i], &exit_status, 0);
		if (i == shell->n_cmd - 1)
		{
			if (WIFEXITED(exit_status) != 0)
				shell->exit_status = WEXITSTATUS(exit_status);
			else if (WIFSIGNALED(exit_status))
				shell->exit_status = WTERMSIG(exit_status) + 128;
		}
		if (WIFSIGNALED(exit_status))
			signal_recieved = 1;
		i++;
	}
	if (signal_recieved)
		printf("\n");
	g_sig = 0;
	ft_ms_signal(shell, EXECUTION);
}
