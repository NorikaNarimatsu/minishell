/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exetransfer.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/24 14:52:48 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/24 14:57:30 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_transfer_pipe(t_token *token, t_exec *exec)
{
	t_exec	*new_exec;

	new_exec = ft_calloc(1, sizeof(t_exec));
	if (!new_exec)
		return (MALERR);
	exec->pipe = new_exec;
	if (ft_transfer_for_exec(token->next, exec->pipe) == MALERR)
		return (MALERR);
	return (0);
}

int	ft_transfer_append(t_token **token, t_exec *exec)
{
	int	fd;

	(*token) = (*token)->next;
	if (exec->flag == -1)
		return (0);
	if (!exec->outfile)
		ft_free_string(&exec->outfile);
	exec->outfile = ft_strdup((*token)->word);
	if (!exec->outfile)
		return (MALERR);
	fd = open(exec->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		exec->flag = fd;
		return (0);
	}
	close(fd);
	exec->is_end_append = true;
	return (0);
}

int	ft_transfer_heredoc(t_token **token, t_exec *exec)
{
	int	i;

	(*token) = (*token)->next;
	i = ft_ms_count_words(exec->heredoc);
	exec->heredoc[i] = ft_strdup((*token)->word);
	if (!exec->heredoc[i])
		return (MALERR);
	exec->is_end_infile = false;
	return (0);
}

int	ft_transfer_input(t_token **token, t_exec *exec)
{
	int	result;

	(*token) = (*token)->next;
	if (exec->flag == -1)
		return (0);
	if (!exec->infile)
		ft_free_string(&exec->infile);
	exec->infile = ft_strdup((*token)->word);
	if (!exec->infile)
		return (MALERR);
	result = access(exec->infile, F_OK | R_OK);
	ft_print_exec_list(exec);
	if (result == -1)
	{
		exec->flag = result;
		return (0);
	}
	exec->is_end_infile = true;
	return (0);
}

int	ft_transfer_output(t_token **token, t_exec *exec)
{
	int	fd;

	(*token) = (*token)->next;
	if (exec->flag == -1)
		return (0);
	if (!exec->outfile)
		ft_free_string(&exec->outfile);
	exec->outfile = ft_strdup((*token)->word);
	if (!exec->outfile)
		return (MALERR);
	fd = open(exec->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		exec->flag = fd;
		return (0);
	}
	close(fd);
	exec->is_end_append = false;
	return (0);
}
