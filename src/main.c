/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/26 12:36:23 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/06/19 12:19:37 by mdraper       ########   odam.nl         */
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
	// print_env(shell.env);
	(void) argc;
	(void) argv;
	rl_outstream = stderr;
	while (1)
	{
		ft_bzero(&shell.ll_token, sizeof(shell.ll_token));
		ft_bzero(&shell.execution, sizeof(shell.execution));
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		ft_expansion(line, shell.env);
		// 1) Expand ($...)
		// 2) Input check (what to check here)?
		/* quotes, starting with pipe, redirections like this: <> or >< after every redirection should be a word*/
		/* Don't forget to make the free function for Execution!!! */
		my_func(line, &shell);

		if (ft_strcmp(shell.execution->word[0], "echo") == 0)
			echo_builtin(shell.execution->word, &shell);
		// ft_interpret(line, env);
		free(line);
	}
	(void)env;
	exit(0);
}

int	main(int argc, char **argv, char **env)
{
	return (ft_minishell(argc, argv, env));
}
