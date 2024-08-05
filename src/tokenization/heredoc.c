/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:37:49 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/05 21:16:46 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_loop(char **heredoc, int delimitor_index, int fd_write)
{
	char	*line;
	int		i;

	if (g_sig == SIGINT)
		return ;
	line = NULL;
	i = ft_ms_count_words(heredoc) - 1;
	dup2(STDIN_FILENO, FDMAX + 1);
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
		{
			dup2(FDMAX + 1, STDIN_FILENO);
			close(FDMAX + 1);
			break ;
		}
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

static int	heredoc_pipe(t_exec *exec)
{
	int	fd[2];
	int	delimitor_index;

	if (pipe(fd) == -1)
		return (perror("pipe"), PIPERR);
	exec->fd_heredoc = fd[0];
	delimitor_index = 0;
	while (exec->heredoc[delimitor_index])
	{
		if (g_sig == SIGINT)
			return (0);
		heredoc_loop(exec->heredoc, delimitor_index, fd[1]);
		delimitor_index++;
	}
	close(fd[1]);
	return (0);
}

int	ft_heredoc(t_shell *shell)
{
	t_exec	*exec;
	int		error;

	error = 0;
	exec = shell->execution;
	shell->execution->fd_heredoc = -1;
	while (exec && g_sig != SIGINT)
	{
		if (exec->heredoc && exec->heredoc[0])
		{
			ft_ms_signal(shell, HEREDOC);
			error = heredoc_pipe(exec);
			if (error < 0)
				return (error);
		}
		exec = exec->pipe;
	}
	return (0);
}
