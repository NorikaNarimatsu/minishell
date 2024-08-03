/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:37:49 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/03 15:30:26 by mdraper       ########   odam.nl         */
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
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_strcmp(line, heredoc[delimitor_index]) == 0)
			break ;
		// WE NEED TO EXPAND HERE!!
		if (delimitor_index == i)
		{
			write(fd_write, line, ft_strlen(line));
			write(fd_write, "\n", 1);
		}
		ft_free_string(&line);
	}
	ft_free_string(&line);
}

int	heredoc_pipe(t_exec *exec)
{
	int	fd[2];
	int	delimitor_index;

	if (pipe(fd) == -1)
		return (perror("pipe"), PIPERR);
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

int	ft_heredoc(t_shell *shell)
{
	t_exec	*exec;

	exec = shell->execution;
	shell->execution->fd_heredoc = -1;
	while (exec)
	{
		if (exec->heredoc && exec->heredoc[0])
		{
			ft_ms_signal(shell, HEREDOC);
			if (heredoc_pipe(exec) == PIPERR)
				return (PIPERR);
		}
		exec = exec->pipe;
	}
	return (0);
}
