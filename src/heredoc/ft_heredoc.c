/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:37:49 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/05 22:07:28 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_reset_heredoc_signal(char *line)
{
	ft_free_string(&line);
	if (dup2(FDMAX + 1, STDIN_FILENO) == -1)
		return (perror("dup2 heredoc"), DUPERR);
	close(FDMAX + 1);
	return (0);
}

static int	heredoc_loop(char **heredoc, int di, int fd_write, t_shell *shell)
{
	char	*line;
	int		i;

	line = NULL;
	i = ft_ms_count_words(heredoc) - 1;
	while (1)
	{
		line = readline("> ");
		if (g_sig == SIGINT)
			return (ft_reset_heredoc_signal(line));
		if (!line)
		{
			printf("warning: here-document delimited by end-of-file\n");
			break ;
		}
		if (ft_expansion_heredoc(&line, shell) == MALERR)
			return (ft_free_string(&line), MALERR);
		if (ft_strcmp(line, heredoc[di]) == 0)
			break ;
		if (di == i)
			ft_putendl_fd(line, fd_write);
		ft_free_string(&line);
	}
	return (ft_free_string(&line), 0);
}

static int	heredoc_pipe(t_shell *shell)
{
	int	fd[2];
	int	del_indx;
	int	error;

	if (pipe(fd) == -1)
		return (perror("pipe"), PIPERR);
	error = 0;
	shell->execution->fd_heredoc = fd[0];
	del_indx = 0;
	while (shell->execution->heredoc[del_indx])
	{
		if (g_sig == SIGINT)
			return (0);
		error = heredoc_loop(shell->execution->heredoc, del_indx, fd[1], shell);
		if (error < 0)
			return (error);
		del_indx++;
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
			if (dup2(STDIN_FILENO, FDMAX + 1) == -1)
				return (perror("dup2 heredoc"), DUPERR);
			error = heredoc_pipe(shell);
			if (error < 0)
				return (error);
		}
		exec = exec->pipe;
	}
	return (0);
}
