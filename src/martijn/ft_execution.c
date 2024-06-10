/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 17:16:21 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/10 20:59:26 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_transfer_pipe(t_token *token, t_exec *exec)
{
	t_exec	*new_exec;

	new_exec = ft_create_exec();
	if (!new_exec)
		return (MALERR);
	exec->pipe = new_exec;
	ft_transfer_for_exec(token->next, exec->pipe);
	return (0);
}

int	ft_transfer_word(t_token *token, t_exec *exec)
{
	int	i;

	i = ft_ms_count_words(exec->word);
	exec->word[i] = ft_strdup(token->word);
	if (!exec->word[i])
		return (MALERR);
	return (0);
}






static int	ft_transfer(t_token *token, t_exec *exec)
{
	if (token->type == T_PIPE)
		return (ft_transfer_pipe(token, exec));
	else if (token->type == T_APPEND)
		return (ft_transfer_append(token, exec));
	else if (token->type == T_HEREDOC)
		return (ft_transfer_heredoc(token, exec));
	else if (token->type == T_INPUT)
		return (ft_transfer_input(token, exec));
	else if (token->type == T_OUTPUT)
		return (ft_transfer_output(token, exec));
	else if (token->type == T_WORD)
		return (ft_transfer_word(token, exec));
	else if (token->type == T_EOF)
		return (ft_transfer_eof(token, exec));
	else if (token->type == T_ENV)
		return (ft_transfer_env(token, exec));
	else
		return (CNFERR);
}

int	ft_transfer_for_exec(t_token *token, t_exec *exec)
{
	t_token	*head_token;
	t_exec	*head_exec;
	int		error;

	error = 0;
	head_token = token;
	head_exec = exec;
	while (token)
	{
		error = ft_transfer(token, exec);
		if (error != 0)
			return (error);
		if (token->type == T_PIPE)
			break ;		
		token->next;
	}
	token = head_token;
	exec = head_exec;
	return (0);
}
