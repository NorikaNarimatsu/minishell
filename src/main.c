/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/22 17:54:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
Still to do:
I don't really need expanding inside the struct.
I only need the line and exit status at the end. So maybe I have to rewrite it a bit?
*/

#include "minishell.h"
void	ft_free_minishell(t_shell *shell)
{
	if (shell->env)
		ft_free_env_list(&shell->env);
	if (shell->expanding)
		ft_free_expansion(&shell->expanding);
	if (shell->ll_token)
		ft_free_t_token(&shell->ll_token);
	if (shell->execution)
		ft_free_s_exec(&shell->execution);
}

int	ft_minishell(char **env)
{
	t_shell	shell;
	char	*line;

	shell.env = ft_init_env(env);
	if (!shell.env)
		return (EXIT_FAILURE);
	shell.expanding = ft_create_expansion();
	if (!shell.expanding)
		return (ft_free_env_list(&shell.env), EXIT_FAILURE);
	while (1)
	{
		// printf("EXIT %d\n", shell.exit_status);
		ft_bzero(&shell.ll_token, sizeof(shell.ll_token));
		ft_bzero(&shell.execution, sizeof(shell.execution));
		shell.expanding->exp_line = NULL;
		// ft_bzero(&shell.expanding, sizeof(shell.expanding));
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		// printf("----- EXPANSION -----\n");
		if (ft_expansion(line, shell.env, shell.expanding) == MALERR)
			return (MALERR); // free_everything function;
		ft_free_string(&line);
		line = shell.expanding->exp_line;
		// printf("----- SYNTAX -----\n");
		if (ft_syntax(line) == 0)
			;
			// printf("No syntax error!\nline=%s\n", line);
		// printf("----- TOKENIZATION -----\n");
		ft_tokenization(line, &shell);
		// printf("----- HEREDOC -----\n");
		if (ft_heredoc(&shell) == -1)
		{
			ft_free_string(&line);
			break ;
		}
		// printf("----- EXECUTION -----\n");
		shell.exit_status = ft_interpret(&shell);
		ft_free_string(&line);
	}

		// ft_free_minishell(&shell);
		// probably use ft_free_expansion(shell.expanding);

	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	return (ft_minishell(env));
}
