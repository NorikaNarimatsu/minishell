/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/24 09:08:00 by mdraper       ########   odam.nl         */
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
	// if ((*shell)->ll_token)
	// 	ft_free_t_token(&(*shell)->ll_token);
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
	shell->execution = ft_create_exec();
	if (!shell->execution)
	{
		ft_free_env_list(&shell->env);
		free(shell);
		shell = NULL;
		return (NULL);
	}
	return (shell);
}

void	ft_reset(t_shell *shell)
{
	ft_free_string(&shell->line);
	if (shell->execution != NULL)
	{
		if (shell->execution->pipe != NULL)
			ft_free_s_exec(&shell->execution->pipe);
		ft_free_array(&shell->execution->word);
		ft_free_string(&shell->execution->infile);
		ft_free_string(&shell->execution->outfile);
		ft_free_array(&shell->execution->heredoc);
		ft_bzero(shell->execution, sizeof(shell->execution));
	}
	shell->token_flag = 1;
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
		ft_reset(shell);
		shell->line = readline("minishell$ ");
		if (!shell->line)
		{
			//the actual function of exit (free anything that was allocated)
			printf("exit\n");
			break ;
		}
		add_history(shell->line);
		// printf("----- EXPANSION -----\n");
		if (ft_expansion(shell) == MALERR)
			return (ft_free_minishell(&shell), MALERR); // free_everything function;
		// printf("----- SYNTAX -----\n");
		if (ft_syntax(shell->line, shell) == SYNERR)		// free_everything function;
			continue ;
		// printf("----- TOKENIZATION -----\n");
		ft_tokenization(shell);		// what is malloc error?
		// printf("----- HEREDOC -----\n");
		if (ft_heredoc(shell) == -1)
			break ;
		// printf("----- EXECUTION -----\n");
		shell->exit_status = ft_interpret(shell);
	}
	return (ft_free_minishell(&shell), 0);
}

int	main(int argc, char **argv, char **env)
{
	(void) argc;
	(void) argv;
	if (argc != 1)
	{
		printf("Wrong input!\n");	// TODO: Optimazation!
		return (1);
	}
	/*
	Here we should handle the signals
	//running program:
	//child program:
	*/
	return (ft_minishell(env));
}
