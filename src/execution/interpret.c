/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:42:57 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/13 17:33:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile_outfile(t_exec *exec)
{
	int	flags;

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

int	execute_single_command(t_shell *shell)
{
	pid_t	pid;
	char	*path;
	int		status;
	char	**envp;

	open_infile_outfile(shell->execution);
	path = shell->execution->word[0];

	if (is_buildin(path))
	{
		if (shell->execution->infile)
		{
			if (dup2(shell->execution->fd_infile, STDIN_FILENO) < 0)
			{
				perror("dup2 infile");
				exit(EXIT_FAILURE);
			}
			close(shell->execution->fd_infile);
		}
		else if (shell->execution->outfile)
		{
			if (dup2(shell->execution->fd_outfile, STDOUT_FILENO) < 0)
			{
				perror("dup2 outfile");
				exit(EXIT_FAILURE);
			}
			close(shell->execution->fd_outfile);
		}
		execute_buildin(shell);
	}
	else
	{
		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			if (shell->execution->infile)
			{
				if (dup2(shell->execution->fd_infile, STDIN_FILENO) < 0)
				{
					perror("dup2 infile");
					exit(EXIT_FAILURE);
				}
				close(shell->execution->fd_infile);
			}
			if (shell->execution->outfile)
			{
				if (dup2(shell->execution->fd_outfile, STDOUT_FILENO) < 0)
				{
					perror("dup2 outfile");
					exit(EXIT_FAILURE);
				}
				close(shell->execution->fd_outfile);
			}
			if (strchr(path, '/') == NULL)
				path = search_path(path);
			validate_access(path, shell->execution->word[0]);
			envp = env_list_to_array(shell->env);
			execve(path, shell->execution->word, envp);
			fatal_error("execve");
		}
		if (shell->execution->fd_infile >= 0)
			close(shell->execution->fd_infile);
		if (shell->execution->fd_outfile >= 0)
			close(shell->execution->fd_outfile);
		wait(&status);
		return (WEXITSTATUS(status));
	}
	return (0);
}



int	ft_interpret(t_shell *shell)
{
	int	num_pipe;

	num_pipe = count_command(shell->execution);
	printf("num of pipe = %d\n", num_pipe);

	if (num_pipe == 1)
		return (execute_single_command(shell));
	// else
	// 	return (execute_pipe_command(shell)); // TODO
	return (0);
}
