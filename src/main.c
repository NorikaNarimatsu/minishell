/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/15 16:32:57 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*line;

	(void) argc;
	(void) argv;
	shell.env = init_env(env);
	shell.expanding = ft_create_expansion();
	if (!shell.expanding)
		return (EXIT_FAILURE); // TO_DO: MALLOC ERROR!
	while (1)
	{
		ft_bzero(&shell.ll_token, sizeof(shell.ll_token));
		ft_bzero(&shell.execution, sizeof(shell.execution));
		shell.expanding->exp_line = NULL;
		shell.expanding->single_double_quote = 0;
		// ft_bzero(&shell.expanding, sizeof(shell.expanding));
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		printf("----- EXPANSION -----\n");
		ft_expansion(line, shell.env, shell.expanding);
		ft_free_string(&line);
		line = shell.expanding->exp_line;
		// 2) Input check (what to check here)?
		/* quotes, starting with pipe, redirections like this: <> or >< after every redirection should be a word*/
		/* Don't forget to make the free function for Execution!!! */
		printf("----- TOKENIZATION -----\n");
		ft_tokenization(line, &shell);
		printf("----- EXECUTION -----\n");
		ft_interpret(&shell);
		ft_free_string(&line);
	}
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	return (ft_minishell(argc, argv, env));
}
