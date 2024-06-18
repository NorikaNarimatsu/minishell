/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/18 14:21:33 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int argc, char **argv, char **env)
{
	char	*line;


	(void) argc;
	(void) argv;
	rl_outstream = stderr;
	while (1)
	{
		line = readline("minishell$ ");
		if (line == NULL)
			break ;
		if (*line)
			add_history(line);
		ft_interpret(line, env);
		free(line);
	}
	exit(0);
}
