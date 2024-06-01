/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 12:36:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/01 19:00:52 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_exit(char *location, char *msg, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, msg); //to do
	exit(status);
}

char	*search_path(char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;

	value = getenv("PATH"); // todo
	while (*value)
	{
		bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			strncpy(path, value, end - value); //todo
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			char	*dup;

			dup = ft_strdup(path);
			if (dup == NULL)
			{
				ft_putstr_fd("pid error\n", 2);
				exit(EXIT_FAILURE);
			}
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

int	ft_interpret(char *line, char **env)
{
	pid_t	pid;
	int		status;
	char *argv[] = {line, NULL};
	char	*path = argv[0];

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
		if (path == NULL)
			error_exit(argv[0], "command not found", 127);
		if (access(path, F_OK) < 0)
			error_exit(argv[0], "command not found", 127);
		execve(path, argv, env);
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
		ft_interpret(line, env);
		free(line);
	}
	exit(0);
}
