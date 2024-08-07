/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/07 23:21:46 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig = 0;

void	ft_print_open_fds(void)
{
	for (int fd = 0; fd < 1024; fd++)
	{
		if (fcntl(fd, F_GETFD) != -1)
			printf("Open FD: %d\n", fd);
	}
}

static int	ft_minishell_parsing(t_shell *shell)
{
	int	error;

	error = 0;
	if (ft_syntax(shell->line, shell) == SYNERR)
		return (SYNERR);
	ft_ms_signal(shell, INTERACTIVE);
	if (ft_expansion(shell) == MALERR)
		return (MALERR);
	if (ft_syntax(shell->line, shell) == SYNERR)
		return (SYNERR);
	if (ft_tokenization(shell) == MALERR)
		return (MALERR);
	error = ft_heredoc(shell);
	if (error < 0)
		return (error);
	return (0);
}

int	ft_minishell(t_shell *shell)
{
	int	error;

	error = 0;
	while (1)
	{
		ft_reset(shell);
		shell->line = readline("minishell$ ");
		if (!shell->line)
			break ;
		add_history(shell->line);
		error = ft_minishell_parsing(shell);
		if (error == SYNERR)
			continue ;
		if (error < 0)
			return (ft_ms_exit(&shell, error));
		if (g_sig == SIGINT)
			continue ;
		shell->exit_status = ft_interpret(shell);
		if (shell->exit_status < 0)
			return (ft_ms_exit(&shell, shell->exit_status));
		// ft_print_open_fds();
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
