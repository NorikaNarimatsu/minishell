/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 09:37:49 by mdraper           #+#    #+#             */
/*   Updated: 2024/07/22 14:33:10 by nnarimat         ###   ########.fr       */
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
		if (ft_strcmp(line, heredoc[delimitor_index]) == 0)
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
		return (ft_putstr_fd("pipe error\n", 2), -1);
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
	while (exec)
	{
		if (exec->heredoc && exec->heredoc[0])
		{
			if (heredoc_pipe(exec) == -1)
				return (-1);
		}
		exec = exec->pipe;
	}
	return (0);
}
