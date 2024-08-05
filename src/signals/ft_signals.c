/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signals.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 10:41:32 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/05 21:21:31 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_interactive(int sig)
{
	g_sig = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_sigint_heredoc(int sig)
{
	g_sig = sig;
	printf("\n");
	close(STDIN_FILENO);
}

static void	ft_sigint_execution(int sig)
{
	g_sig = sig;
	printf("\n");
}

static void	ft_sigquit_execution(int sig)
{
	g_sig = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
}

int	ft_ms_signal(t_shell *shell, int mode)
{
	if (mode == INTERACTIVE)
	{
		shell->sa_int.sa_handler = ft_sigint_interactive;
		shell->sa_quit.sa_handler = SIG_IGN;
	}
	if (mode == HEREDOC)
		shell->sa_int.sa_handler = ft_sigint_heredoc;
	else if (mode == EXECUTION)
	{
		shell->sa_int.sa_handler = ft_sigint_execution;
		shell->sa_quit.sa_handler = ft_sigquit_execution;
	}
	else if (mode == IGNORE)
	{
		shell->sa_int.sa_handler = SIG_IGN;
		shell->sa_quit.sa_handler = SIG_IGN;
	}
	if (sigaction(SIGINT, &shell->sa_int, NULL) == -1)
		exit(EXIT_FAILURE);				// UPDATE THIS!!
	else if (sigaction(SIGQUIT, &shell->sa_quit, NULL) == -1)
		exit(EXIT_FAILURE);				// UPDATE THIS!!
	if (g_sig > 0)
	{
		shell->exit_status = g_sig + 128;
		g_sig = 0;
	}
	return (0);
}

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
