/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_signals.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 10:41:32 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/07 10:08:07 by mdraper       ########   odam.nl         */
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
		ft_ms_exit(&shell, SIGERR);
	else if (sigaction(SIGQUIT, &shell->sa_quit, NULL) == -1)
		ft_ms_exit(&shell, SIGERR);
	ft_recieved_signal_exit_status(shell);
	return (0);
}
