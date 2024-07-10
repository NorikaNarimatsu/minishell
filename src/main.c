/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 14:00:02 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fatal_error(char *message)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", message);
	exit(1);
}

void	error_exit(char *location, char *message, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, message); //to do
	exit(status);
}

int	exec(char **argv, char **env)
{
	pid_t	pid;
	char	*path = argv[0];
	int		status;

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("pid error\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (ft_strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, argv[0]);
		execve(path, argv, env);
		fatal_error("Execve");
	}

	wait(&status);
	return (WEXITSTATUS(status));
}

int	ft_interpret(char *line, char **env)
{
	int		status;
	char	*argv[] = {line, NULL};

	status = exec(argv, env);
	return (status);
}

int	ft_minishell(int argc, char **argv, char **env)
{
	t_shell	shell;
	char	*line;

	shell.env = init_env(env);
	shell.expanding = ft_create_expansion();
	if (!shell.expanding)
		return (EXIT_FAILURE); // TO_DO: MALLOC ERROR!
	// print_env(shell.env);
	(void) argc;
	(void) argv;
	rl_outstream = stderr;
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
		// if (ft_strcmp(shell.execution->word[0], "echo") == 0) // this can get segfault!?
		// 	echo_builtin(shell.execution->word, &shell);

		which_buildin(&shell);

		// ft_interpret(line, env);
		ft_free_string(&line);
	}
	(void)env;
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	return (ft_minishell(argc, argv, env));
}
