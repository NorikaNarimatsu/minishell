/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   interpret.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 16:42:57 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/16 11:15:53 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	ft_execute_command(t_exec *exec, t_env *env)
{
	char	*path;
	char	**envp;

	path = exec->word[0];
	envp = ft_env_to_array(env);
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

int	ft_execute_single(t_shell *shell)
{
	pid_t	pid;
	int		status;

	ft_open_files(shell->execution);
	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		ft_execute_command(shell->execution, shell->env);
	else
	{
		waitpid(pid, &status, 0);
		return (WEXITSTATUS(status));
	}
	return (0);
}

void	ft_setup_pipes(int *fd, int num_cmnds)
{
	int	i;

	i = 0;
	while (i < num_cmnds)
	{
		if (pipe(fd + 2 * i) < 0)
			ft_fatal_error("pipe");
		i++;
	}
}


void	ft_handle_command(t_exec *exec, int *fd, int num_cmnd, int index, t_env *env)
{
	int	i;

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
	ft_open_files(exec);
	ft_execute_command(exec, env);
}


int	ft_execute_pipe(t_exec *exec, t_env *env, int num_cmnd)
{
	t_exec	*head;
	int		*fd;
	int		index;
	pid_t	pid;
	int		i;

	head = exec->pipe;
	index = 0;
	fd = malloc(2 * (num_cmnd - 1) * sizeof(int));
	if (!fd)
		ft_fatal_error("malloc");
	ft_setup_pipes(fd, num_cmnd - 1);
	while (exec)
	{
		pid = fork();
		if (pid < 0)
			ft_fatal_error("fork");
		else if (pid == 0)
			ft_handle_command(exec, fd, num_cmnd, index, env);
		index++;
		exec = exec->pipe;
	}
	exec = head;
	i = 0;
	while (i < 2 * (num_cmnd - 1))
		close(fd[i++]);
	i = 0;
	while (i++ < num_cmnd)
		wait(NULL);
	free(fd);
	return (0);
}


int	ft_interpret(t_shell *shell)
{
	int	num_cmnd;

	num_cmnd = ft_count_command(shell->execution);
	if (num_cmnd == 1)
		return (ft_execute_single(shell));
	else
		return (ft_execute_pipe(shell->execution, shell->env, num_cmnd));
	return (0);
}



// int	ft_execute_pipe(t_shell *shell, int num_commands)
// {
// 	t_exec	*current;
// 	int		fd[2 * (num_commands - 1)];
// 	int		i;
// 	int		command_index;
// 	pid_t	pid;

// 	current = shell->execution;
// 	command_index = 0;
// 	for (i = 0; i < num_commands - 1; i++)
// 	{
// 		if (pipe(fd + 2 * i) < 0)
// 			ft_fatal_error("pipe");
// 	}
// 	while (current)
// 	{
// 		pid = fork();
// 		if (pid < 0)
// 			ft_fatal_error("fork");
// 		else if (pid == 0)
// 		{
// 			if (command_index > 0)
// 			{
// 				if (dup2(fd[2 * (command_index - 1)], STDIN_FILENO) < 0)
// 					ft_fatal_error("dup2 stdin");
// 			}
// 			if (command_index < num_commands - 1)
// 			{
// 				if (dup2(fd[2 * command_index + 1], STDOUT_FILENO) < 0)
// 					ft_fatal_error("dup2 stdout");
// 			}
// 			for (i = 0; i < 2 * (num_commands - 1); i++)
// 				close(fd[i]);
// 			ft_open_files(current);
// 			ft_execute_command(current, shell->env);
// 		}
// 		command_index++;
// 		current = current->pipe;
// 	}
// 	for (i = 0; i < 2 * (num_commands - 1); i++)
// 		close(fd[i]);
// 	for (i = 0; i < num_commands; i++)
// 		wait(NULL);
// 	return (0);
// }