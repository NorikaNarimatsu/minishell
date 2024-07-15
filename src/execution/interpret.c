/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:42:57 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/15 14:26:51 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	open_infile_outfile(t_exec *exec)
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

void	execute_command(t_exec *exec, t_env *env)
{
	char	*path;
	char	**envp;

	path = exec->word[0];
	envp = env_list_to_array(env);
	if (exec->fd_infile != -1)
	{
		if (dup2(exec->fd_infile, STDIN_FILENO) < 0)
		{
			perror("dup2 infile");
			exit(EXIT_FAILURE);
		}
		close(exec->fd_infile);
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
	if (is_builtin(path))
	{
		execute_builtin(exec, env);
		exit(0);
	}
	else
	{
		if (strchr(path, '/') == NULL)
			path = search_path(path);
		validate_access(path, exec->word[0]);
		execve(path, exec->word, envp);
		fatal_error("execve");
	}
}

int	execute_single_command(t_shell *shell)
{
	pid_t	pid;
	int		status;

	open_infile_outfile(shell->execution);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		printf("hello\n");
		execute_command(shell->execution, shell->env);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

int execute_pipe_command(t_shell *shell)
{
	t_exec *current = shell->execution;
	int num_commands = count_command(current);
	int pipefd[2 * (num_commands - 1)];
	int i;

	// Create pipes
	for (i = 0; i < num_commands - 1; i++) {
		if (pipe(pipefd + 2 * i) < 0) {
			fatal_error("pipe");
		}
	}

	int command_index = 0;
	while (current) {
		pid_t pid = fork();
		if (pid < 0) {
			fatal_error("fork");
		} else if (pid == 0) {
			// Set up input redirection
			if (command_index > 0) {
				if (dup2(pipefd[2 * (command_index - 1)], STDIN_FILENO) < 0) {
					fatal_error("dup2 stdin");
				}
			}
			// Set up output redirection
			if (command_index < num_commands - 1) {
				if (dup2(pipefd[2 * command_index + 1], STDOUT_FILENO) < 0) {
					fatal_error("dup2 stdout");
				}
			}

			// Close all pipe file descriptors
			for (i = 0; i < 2 * (num_commands - 1); i++) {
				close(pipefd[i]);
			}

			// Open infile and outfile if needed
			open_infile_outfile(current);

			// Execute the command
			execute_command(current, shell->env);
		}

		command_index++;
		current = current->pipe;
	}

	// Close all pipe file descriptors in the parent
	for (i = 0; i < 2 * (num_commands - 1); i++) {
		close(pipefd[i]);
	}

	// Wait for all child processes
	for (i = 0; i < num_commands; i++) {
		wait(NULL);
	}

	return 0;
}

int	ft_interpret(t_shell *shell)
{
	int	num_pipe;

	num_pipe = count_command(shell->execution);
	printf("num of pipe = %d\n", num_pipe);

	if (num_pipe == 1)
		return (execute_single_command(shell));
	else
		return (execute_pipe_command(shell));
	return (0);
}


/*
int	execute_pipe_command(t_shell *shell)
{
	t_exec *exec = shell->execution;
	int num_commands = count_command(exec);
	int pipefd[2 * (num_commands - 1)];
	int i = 0;

	// Create pipes
	for (i = 0; i < num_commands - 1; i++)
	{
		if (pipe(pipefd + i * 2) < 0) {
			perror("pipe");
			exit(EXIT_FAILURE);
		}
	}

	int command_index = 0;
	while (exec)
	{
		pid_t pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0) {
			if (command_index < num_commands - 1)
			{
				if (dup2(pipefd[command_index * 2 + 1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (command_index > 0)
			{
				if (dup2(pipefd[(command_index - 1) * 2], STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}

			// Close all pipe descriptors in child process
			for (i = 0; i < 2 * (num_commands - 1); i++) {
				close(pipefd[i]);
			}
			execute_command(shell); // Execute the command
		}
		command_index++;
		exec = exec->pipe;
	}

	// Close all pipe descriptors in parent process
	for (i = 0; i < 2 * (num_commands - 1); i++) {
		close(pipefd[i]);
	}

	// Wait for all child processes
	for (i = 0; i < num_commands; i++) {
		wait(NULL);
	}

	return 0;
}
*/