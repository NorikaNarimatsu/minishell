/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redirect.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/17 11:56:22 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/19 20:58:47 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to open input and output files
void	ft_open_io(t_exec *exec)
{
	int	flags;

	exec->fd_infile = -1;
	exec->fd_outfile = -1;
	printf("OPENING IO...with [in:%s] and [out:%s]\n", exec->infile, exec->outfile);
	if (exec->infile)
	{
		exec->fd_infile = open(exec->infile, O_RDONLY);
		if (exec->fd_infile < 0)
		{
			perror(exec->infile);
			exit(EXIT_FAILURE);
		}
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
			perror(exec->outfile);
			if (exec->fd_infile >= 0)
				close(exec->fd_infile);
			exit(EXIT_FAILURE);
		}
	}
}

// Function to redirect input and output
// CHECK: not closing fd_infile if heredoc is last?
void	ft_redirect_io(t_exec *exec)
{
	printf("Redirecting IO...with [in:%s] and [out:%s]\n", exec->infile, exec->outfile);
	if (exec->fd_infile != -1 && exec->is_end_infile)
	{
		if (dup2(exec->fd_infile, STDIN_FILENO) < 0)
		{
			perror("dup2 infile");
			exit(EXIT_FAILURE);
		}
		close(exec->fd_infile);
	}
	else if (exec->fd_heredoc != -1 && !exec->is_end_infile)
	{
		if (dup2(exec->fd_heredoc, STDIN_FILENO) < 0)
		{
			perror("dup2 heredoc");
			exit(EXIT_FAILURE);
		}
		close(exec->fd_heredoc);
	}
	if (exec->fd_outfile != -1)
	{
		printf("hello\n");
		if (dup2(exec->fd_outfile, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");
			exit(EXIT_FAILURE);
		}
		printf("current command is %s\n", exec->word[0]);
		close(exec->fd_outfile);
	}
}

// Function to restore original stdin and stdout
void	ft_restore_io(int saved_stdin, int saved_stdout)
{
	if (dup2(saved_stdin, STDIN_FILENO) < 0)
	{
		perror("dup2 restore stdin");
		exit(EXIT_FAILURE);
	}
	if (dup2(saved_stdout, STDOUT_FILENO) < 0)
	{
		perror("dup2 restore stdout");
		exit(EXIT_FAILURE);
	}
	close(saved_stdin);
	close(saved_stdout);
}
