/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signals.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 10:41:32 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/30 18:47:45 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_sigint_interactive(int sig)
{
	SIGNAL_NR = sig;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_sigint_heredoc(int sig)
{
	SIGNAL_NR = sig;
	printf("\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void	ft_sigint_execution(int sig)
{
	SIGNAL_NR = sig;
	printf("\n");
}

static void	ft_sigquit_execution(int sig)
{
	SIGNAL_NR = sig;
	printf("Quit (core dumped)\n");
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
	{
		shell->sa_int.sa_handler = ft_sigint_heredoc;
		shell->sa_quit.sa_handler = SIG_IGN;
	}
	else if (mode == EXECUTION)
	{
		shell->sa_int.sa_handler = ft_sigint_execution;
		shell->sa_quit.sa_handler = ft_sigquit_execution;
	}
	if (sigaction(SIGINT, &shell->sa_int, NULL) == -1)
		exit(EXIT_FAILURE);
	else if (sigaction(SIGQUIT, &shell->sa_quit, NULL) == -1)
		exit(EXIT_FAILURE);
	if (SIGNAL_NR > 0)
	{
		shell->exit_status = SIGNAL_NR + 128;
		SIGNAL_NR = 0;
	}
	return (0);
}
