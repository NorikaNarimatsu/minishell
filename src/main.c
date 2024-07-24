/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/24 15:54:02 by mdraper       ########   odam.nl         */
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
		return (ft_free_minishell(&shell), NULL);
	shell->execution = ft_calloc(1, sizeof(t_exec));
	if (!shell->execution)
		return (ft_free_minishell(&shell), NULL);
	return (shell);
}

static void	ft_reset(t_shell *shell)
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
		shell->execution->fd_infile = 8;
		shell->execution->is_end_append = 1;
		ft_bzero(shell->execution, sizeof(t_exec));
	}
	shell->token_flag = 1;
	shell->n_cmd = 0;
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
		if (ft_syntax(shell->line, shell) == SYNERR)	// Can be MALLOC error or SYNTAX error!
			continue ;
		// printf("----- TOKENIZATION -----\n");
		if (ft_tokenization(shell) == MALERR)
			return (ft_free_minishell(&shell), MALERR); // free_everything function;
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
