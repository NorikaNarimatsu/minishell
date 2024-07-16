/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:37:49 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/16 09:42:42 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	heredoc_loop(t_shell *shell, int delimitor_index, int fd_write)
// {
// 	char	*line;
// 	while(1)
// 	{
// 		line = readline(">");
// 		if (strcmp(line, shell->execution->heredoc[delimitor_index]) == 0)
// 			break;

// 		// printout?
// 		free(line);
			
// 	}
// }

// int	heredoc_pipe(t_shell *shell)
// {
// 	int	fd[2];
// 	int	delimitor_index;

// 	if (pipe(fd) == -1)
// 	{
// 		return (printf("pipe error\n"), -1);
// 	}
// 	shell->execution->infile = fd[0];
// 	delimitor_index = 0;
// 	while (shell->execution->heredoc[delimitor_index])
// 	{
// 		heredoc_loop(shell, delimitor_index, fd[1]);
// 		i++;
// 	}

// }

// // make the array of delimintors (char **)

// int	ft_heredoc(t_shell *shell)
// {
// 	t_exec *cmd;

// 	cmd = shell->execution;
// 	while(cmd)
// 	{

// 		cmd = cmd->pipe;
// 	}
// 	return (0)
// }
