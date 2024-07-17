/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:37:49 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/17 16:31:41 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_loop(char **heredoc, int delimitor_index, int fd_write)
{
	char	*line;
	int		i;

	line = NULL;
	i = ft_ms_count_words(heredoc) - 1;
	while (1)
	{
		line = readline("> ");
		if (ft_strcmp(line, heredoc[delimitor_index]) == 0) // ask chriss fr strncmp
		{
			free(line);
			break ;
		}
		else if (delimitor_index == i)
		{
			write(fd_write, line, strlen(line));
			write(fd_write, "\n", 1);
		}
		free(line);
	}
}

int	heredoc_pipe(t_exec *exec)
{
	int	fd[2];
	int	delimitor_index;

	if (pipe(fd) == -1)
		return (printf("pipe error\n"), -1);
	exec->fd_heredoc = fd[0];
	delimitor_index = 0;
	while (exec->heredoc[delimitor_index])
	{
		heredoc_loop(exec->heredoc, delimitor_index, fd[1]);
		delimitor_index++;
	}
	close(fd[1]);
	return (0);
}

// make the array of delimintors (char **)

int	ft_heredoc(t_shell *shell)
{
	t_exec	*exec;

	// shell->execution->fd_infile = -1;
	exec = shell->execution;
	while (exec)
	{
		if (exec->heredoc && exec->heredoc[0]) // char **
		{
			if (heredoc_pipe(exec) == -1)
				return (-1);
		}
		exec = exec->pipe;
	}

	return (0);
}
