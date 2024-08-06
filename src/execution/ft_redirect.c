/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redirect.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:22 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/06 23:37:05 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_io(t_exec *exec)
{
	int	flags;

	exec->fd_infile = -1;
	exec->fd_outfile = -1;
	if (exec->infile)
	{
		exec->fd_infile = open(exec->infile, O_RDONLY);
		if (exec->fd_infile == -1)
			return (perror(exec->infile), 1);
	}
	if (exec->outfile)
	{
		if (exec->is_end_append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		exec->fd_outfile = open(exec->outfile, flags, 0644);
		if (exec->fd_outfile == -1)
		{
			if (exec->fd_infile >= 0)
				close(exec->fd_infile);
			return (perror(exec->outfile), 1);
		}
	}
	return (0);
}

int	ft_redirect_io(t_exec *exec)
{
	if (exec->fd_infile != -1 && exec->is_end_infile == true)
	{
		if (dup2(exec->fd_infile, STDIN_FILENO) == -1)
			return (perror("dup2 infile"), DUPERR);
		close(exec->fd_infile);
	}
	else if (exec->fd_heredoc != -1 && exec->is_end_infile == false)
	{
		if (dup2(exec->fd_heredoc, STDIN_FILENO) == -1)
			return (perror("dup2 heredoc"), DUPERR);
		close(exec->fd_heredoc);
	}
	if (exec->fd_outfile != -1)
	{
		if (dup2(exec->fd_outfile, STDOUT_FILENO) == -1)
			return (perror("dup2 outfile"), DUPERR);
		close(exec->fd_outfile);
	}
	return (0);
}

static int	ft_redirect_pipe(t_shell *shell, t_exec *exec, int *fd, int i)
{
	if (i > 0 && !exec->infile && !exec->heredoc[0])
	{
		if (dup2(fd[2 * (i - 1)], STDIN_FILENO) == -1)
			return (perror("dup2 stdin pipe"), DUPERR);
		close(fd[2 * (i - 1)]);
		fd[2 * (i - 1)] = -1;
	}
	if (i < shell->n_cmd - 1 && !exec->outfile)
	{
		if (dup2(fd[2 * i + 1], STDOUT_FILENO) == -1)
			return (perror("dup2 stdout pipe"), DUPERR);
		close(fd[2 * i + 1]);
		fd[2 * i + 1] = -1;
	}
	return (0);
}

int	ft_restore_io(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) == -1)
		return (perror("dup2 stdin"), DUPERR);
	if (dup2(saved_stdout, STDOUT_FILENO) == -1)
		return (perror("dup2 stdout"), DUPERR);
	close(saved_stdin);
	close(saved_stdout);
	return (0);
}

void	ft_manage_redirect(t_shell *shell, t_exec *exec, int *fd, int i)
{
	if (ft_open_io(exec) == 1)
		exit(EXIT_FAILURE);
	if (ft_redirect_io(exec) == DUPERR)
		exit(EXIT_FAILURE);
	if (ft_redirect_pipe(shell, exec, fd, i) == DUPERR)
		exit(EXIT_FAILURE);
	i = 0;
	while (i < 2 * (shell->n_cmd - 1))
	{
		close(fd[i]);
		fd[i] = -1;
		i++;
	}
}
