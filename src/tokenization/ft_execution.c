/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_execution.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/10 17:16:21 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/24 14:55:06 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_transfer_word(t_token *token, t_exec *exec)
{
	int	i;

	i = ft_ms_count_words(exec->word);
	exec->word[i] = ft_strdup(token->word);
	if (!exec->word[i])
		return (MALERR);
	return (0);
}

static int	ft_transfer(t_token **token, t_exec *exec)
{
	if ((*token)->type == T_WORD)
		return (ft_transfer_word(*token, exec));
	else if ((*token)->type == T_PIPE)
		return (ft_transfer_pipe(*token, exec));
	else if ((*token)->type == T_APPEND)
		return (ft_transfer_append(token, exec));
	else if ((*token)->type == T_HEREDOC)
		return (ft_transfer_heredoc(token, exec));
	else if ((*token)->type == T_INPUT)
		return (ft_transfer_input(token, exec));
	else if ((*token)->type == T_OUTPUT)
		return (ft_transfer_output(token, exec));
	else
		return (0);
}

static int	ft_caltype(t_token *token, enum e_token type)
{
	t_token	*head;
	int		i;

	i = 0;
	head = token;
	while (token)
	{
		if (token->type == type)
			i++;
		if (token->type == T_PIPE)
			break ;
		token = token->next;
	}
	token = head;
	return (i);
}

int	ft_transfer_for_exec(t_token *token, t_exec *exec)
{
	t_token	*head_token;
	t_exec	*head_exec;

	head_token = token;
	head_exec = exec;
	exec->word = ft_calloc(ft_caltype(token, T_WORD) + 1, sizeof(char *));
	if (!exec->word)
		return (MALERR);
	exec->heredoc = ft_calloc(ft_caltype(token, T_HEREDOC) + 1, sizeof(char *));
	if (!exec->heredoc)
		return (MALERR);
	while (token)
	{
		if (ft_transfer(&(token), exec) == MALERR)
			return (MALERR);
		if (token->type == T_PIPE)
			break ;
		token = token->next;
	}
	token = head_token;
	exec = head_exec;
	return (0);
}
