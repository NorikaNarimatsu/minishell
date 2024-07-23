/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/23 10:34:50 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/*
Still to do:
I don't really need expanding inside the struct.
I only need the line and exit status at the end. So maybe I have to rewrite it a bit?
*/

#include "minishell.h"

void	ft_free_minishell(t_shell **shell)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->line)
		ft_free_string(&(*shell)->line);
	if ((*shell)->env)
		ft_free_env_list(&(*shell)->env);
	if ((*shell)->ll_token)
		ft_free_t_token(&(*shell)->ll_token);
	if ((*shell)->execution)
		ft_free_s_exec(&(*shell)->execution);
	free(*shell);
	*shell = NULL;
}

t_shell	*ft_init_shell(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = ft_init_env(env);
	if (!shell->env)
	{
		free(shell);
		shell = NULL;
		return (NULL);
	}
	return (shell);
}

int	ft_minishell(char **env)
{
	t_shell	*shell;

	shell = ft_init_shell(env);
	if (!shell)
		return (EXIT_FAILURE);
	while (1)
	{
		// printf("EXIT %d\n", shell.exit_status);
		ft_bzero(&shell->ll_token, sizeof(shell->ll_token));
		ft_bzero(&shell->execution, sizeof(shell->execution));
		ft_free_string(&shell->line);
		shell->line = readline("minishell$ ");
		if (!shell->line)
			break ;
		add_history(shell->line);
		// printf("----- EXPANSION -----\n");
		if (ft_expansion(shell) == MALERR)
			return (MALERR); // free_everything function;
		// printf("----- SYNTAX -----\n");
		if (ft_syntax(shell->line) == 0)
			;
		// printf("----- TOKENIZATION -----\n");
		ft_tokenization(shell);		// what is malloc error?
		// printf("----- HEREDOC -----\n");
		if (ft_heredoc(shell) == -1)
			break ;
		// printf("----- EXECUTION -----\n");
		shell->exit_status = ft_interpret(shell);
	}
	ft_free_minishell(&shell);
	return (ft_free_minishell(&shell), 0);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	return (ft_minishell(env));
}
