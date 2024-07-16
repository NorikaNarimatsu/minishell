/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/16 11:36:10 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_minishell(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*line;

	(void) argc;
	(void) argv;
	shell.env = ft_init_env(env);
	shell.expanding = ft_create_expansion();
	if (!shell.expanding)
		return (EXIT_FAILURE); // TO_DO: MALLOC ERROR!
	while (1)
	{
		ft_bzero(&shell.ll_token, sizeof(shell.ll_token));
		ft_bzero(&shell.execution, sizeof(shell.execution));
		shell.expanding->exp_line = NULL;
		// ft_bzero(&shell.expanding, sizeof(shell.expanding));
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		printf("----- EXPANSION -----\n");
		if (ft_expansion(line, shell.env, shell.expanding) == MALERR)
			return (MALERR); // free_everything function;
		ft_free_string(&line);
		line = shell.expanding->exp_line;
		printf("----- SYNTAX -----\n");
		if (ft_syntax(line) == 0)
			printf("No syntax error!\nline=%s\n", line);
		printf("----- TOKENIZATION -----\n");
		ft_tokenization(line, &shell);

		printf("----- HEREDOC -----\n");
		ft_heredoc(&shell);
		
		printf("----- EXECUTION -----\n");
		ft_interpret(&shell);
		ft_free_string(&line);
	}
	(void)env;
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	return (ft_minishell(argc, argv, env));
}
