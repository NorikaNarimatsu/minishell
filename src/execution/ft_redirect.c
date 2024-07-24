/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:22 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/24 15:37:17 by nnarimat         ###   ########.fr       */
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
		if (exec->fd_infile < 0)
			return (perror(exec->infile), EXIT_FAILURE);
	}
	if (exec->outfile)
	{
		if (exec->is_end_append)
			flags = O_WRONLY | O_CREAT | O_APPEND;
		else
			flags = O_WRONLY | O_CREAT | O_TRUNC;
		exec->fd_outfile = open(exec->outfile, flags, 0644);
		if (exec->fd_outfile < 0)
		{
			if (exec->fd_infile >= 0)
				close(exec->fd_infile);
			return (perror(exec->outfile), EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

void	ft_redirect_io(t_exec *exec)
{
	if (exec->fd_infile != -1 && exec->is_end_infile)
	{
		if (dup2(exec->fd_infile, STDIN_FILENO) < 0)
			ft_error_exit("dup2 infle error\n", EXIT_FAILURE);
		close(exec->fd_infile);
	}
	else if (exec->fd_heredoc != -1 && !exec->is_end_infile)
	{
		if (dup2(exec->fd_heredoc, STDIN_FILENO) < 0)
			ft_error_exit("dup2 heredoc error\n", EXIT_FAILURE);
		close(exec->fd_heredoc);
	}
	if (exec->fd_outfile != -1)
	{
		if (dup2(exec->fd_outfile, STDOUT_FILENO) < 0)
			ft_error_exit("dup2 outfile error\n", EXIT_FAILURE);
		close(exec->fd_outfile);
	}
}

void	ft_restore_io(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
		ft_error_exit("dup2 restore stdin error\n", EXIT_FAILURE);
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
		ft_error_exit("dup2 restore stdout error\n", EXIT_FAILURE);
	close(saved_stdin);
	close(saved_stdout);
}
