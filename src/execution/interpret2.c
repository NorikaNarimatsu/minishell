/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:56:22 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 13:53:34 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to open input and output files
void	ft_open_files(t_exec *exec)
{
	int	flags;

	exec->fd_infile = -1;
	exec->fd_outfile = -1;
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
		if (exec->append)
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
void	ft_redirect_io(t_exec *exec)
{
	printf("Redirecting IO...\n");
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
		if (dup2(exec->fd_outfile, STDOUT_FILENO) < 0)
		{
			perror("dup2 outfile");
			exit(EXIT_FAILURE);
		}
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

// Function to execute a command
void	ft_execute_command(t_exec *exec, t_env *env)
{
	char	*path;
	char	**envp;

	path = exec->word[0];
	envp = ft_env_to_array(env);
	if (is_builtin(path))
	{
		ft_execute_builtin(exec, env);
		exit(0);
	}
	else
	{
		if (strchr(path, '/') == NULL)
			path = ft_search_path(path, env);
		ft_validate_access(path, exec->word[0]);
		execve(path, exec->word, envp);
		ft_fatal_error("execve");
	}
}

// Function to handle a command in a pipeline
void	ft_handle_command(t_exec *exec, int *fd, int num_cmnd, int index, t_env *env)
{
	int	i;

	ft_open_files(exec);
	ft_redirect_io(exec);

	if (index > 0)
	{
		if (dup2(fd[2 * (index - 1)], STDIN_FILENO) < 0)
			ft_fatal_error("dup2 stdin");
	}
	if (index < num_cmnd - 1)
	{
		if (dup2(fd[2 * index + 1], STDOUT_FILENO) < 0)
			ft_fatal_error("dup2 stdout");
	}
	i = 0;
	while (i < 2 * (num_cmnd - 1))
		close(fd[i++]);
	ft_execute_command(exec, env);
}
