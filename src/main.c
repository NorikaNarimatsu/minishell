/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/05 21:20:05 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

int	ft_minishell(t_shell *shell)
{
	while (1)
	{
		ft_reset(shell);
		shell->line = readline("minishell$ ");
		if (!shell->line)
			break ;
		add_history(shell->line);
		if (ft_syntax(shell->line, shell) == SYNERR)
			continue ;
		ft_ms_signal(shell, INTERACTIVE);
		if (ft_expansion(shell) == MALERR)
			return (ft_ms_exit(&shell, MALERR));
		if (ft_syntax(shell->line, shell) == SYNERR)
			continue ;
		if (ft_tokenization(shell) == MALERR)
			return (ft_ms_exit(&shell, MALERR));
		if (ft_heredoc(shell) == PIPERR)
			return (ft_ms_exit(&shell, PIPERR));
		if (g_sig == SIGINT)
			continue ;
		shell->exit_status = ft_interpret(shell);
		if (shell->exit_status < 0)
			return (ft_ms_exit(&shell, shell->exit_status));
	}
	return (ft_ms_exit(&shell, 0));
}

int	main(int argc, char **argv, char **env)
{
	t_shell	*shell;

	(void) argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell: too many arguments\n", 2);
		return (1);
	}
	shell = ft_init_shell(env);
	if (!shell)
		return (ft_ms_exit(&shell, MALERR));
	return (ft_minishell(shell));
}
