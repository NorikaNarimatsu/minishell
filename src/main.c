/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/17 18:21:20 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		// printf("adress env=%p\n", shell.env);
		// ft_free_env_list(&shell.env);
		// printf("adress env=%p\n", shell.env);
		ft_free_string(&line);
		line = shell.expanding->exp_line;
		printf("----- SYNTAX -----\n");
		if (ft_syntax(line) == 0)
			printf("No syntax error!\nline=%s\n", line);
		printf("----- TOKENIZATION -----\n");
		if (ft_tokenization(line, &shell) < 0)
			return (printf("probably malloc error\n"), MALERR); // free_everything function;
		printf("----- HEREDOC -----\n");
		ft_heredoc(&shell);
		printf("----- EXECUTION -----\n");
		ft_interpret(&shell);
		ft_free_string(&line);
		// probably use ft_free_expansion(shell.expanding);
	}
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	return (ft_minishell(env));
}
