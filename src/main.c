/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/01 11:23:09 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pipex(char *line, char **env)
{
	pid_t	pid;
	int		status;
	char	*argv[] = {line, NULL};

	pid = fork();
	if (pid < 0)
	{
		ft_putstr_fd("pid error\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(line, argv, env);
		ft_putstr_fd("evecve error\n", 2);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		return (WEXITSTATUS(status));
	}
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
		ft_pipex(line, env);
		free(line);
	}
	exit(0);
}
