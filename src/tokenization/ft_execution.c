/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:16:21 by mdraper           #+#    #+#             */
/*   Updated: 2024/07/16 21:10:48 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_transfer_pipe(t_token *token, t_exec *exec)
{
	t_exec	*new_exec;

	new_exec = ft_create_exec();	// This function is not needed!
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
	{
		printf("Malloc error\n");	// TO_DO: ERROR!
		return (0);
	}
	fd = open(exec->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		exec->flag = fd;
		printf("Permission denied\n");	// TO_DO: ERROR!
		return (0);
	}
	close(fd);
	exec->append = true;
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
	{
		printf("Malloc error\n");	// TO_DO: ERROR!
		return (0);
	}
	result = access(exec->infile, F_OK | R_OK);
	if (result == -1)
	{
		exec->flag = result;
		printf("Permission denied\n");	// TO_DO: ERROR!
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
	{
		printf("Malloc error\n");	// TO_DO: ERROR!
		return (0);
	}
	fd = open(exec->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		exec->flag = fd;
		printf("Permission denied\n");	// TO_DO: ERROR!
		return (0);
	}
	close(fd);
	exec->append = false;
	return (0);
}

int	ft_transfer_eof(t_token *token, t_exec *exec)
{
	(void)token;
	(void)exec;
	return (0);
}

int	ft_transfer_env(t_token *token, t_exec *exec)
{
	(void)token;
	(void)exec;
	return (0);
}

static int	ft_transfer(t_token **token, t_exec *exec)
{
	if ((*token)->type == T_PIPE)
		return (ft_transfer_pipe(*token, exec));
	else if ((*token)->type == T_APPEND)
		return (ft_transfer_append(token, exec));
	else if ((*token)->type == T_HEREDOC)
		return (ft_transfer_heredoc(token, exec));
	else if ((*token)->type == T_INPUT)
		return (ft_transfer_input(token, exec));
	else if ((*token)->type == T_OUTPUT)
		return (ft_transfer_output(token, exec));
	else if ((*token)->type == T_WORD)
		return (ft_transfer_word(*token, exec));
	else if ((*token)->type == T_EOF)
		return (ft_transfer_eof(*token, exec));
	else if ((*token)->type == T_ENV)
		return (ft_transfer_env(*token, exec));
	else
		return (CNFERR);
}

int	ft_count_words(t_token *token)
{
	t_token	*head;
	int		i;

	i = 0;
	head = token;
	while (token)
	{
		if (token->type == T_WORD)
			i++;
		if (token->type == T_PIPE)
			break ;
		token = token->next;
	}
	token = head;
	return (i);
}

int	ft_count_type(t_token *token, enum e_token type)
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
	int		error;

	error = 0;
	head_token = token;
	head_exec = exec;
	exec->word = (char **)ft_calloc(ft_count_words(token) + 1, sizeof(char *));
	if (!exec->word)
		return (printf("Malloc error here!\n"), MALERR);
	exec->heredoc = ft_calloc(ft_count_type(token, T_HEREDOC) + 1, sizeof(char *));
	if (!exec->heredoc)
		return (printf("Malloc error here!\n"), MALERR);
	while (token)
	{
		error = ft_transfer(&(token), exec);
		if (error != 0)
			return (error);
		if (token->type == T_PIPE)
			break ;
		token = token->next;
	}
	token = head_token;
	exec = head_exec;
	return (0);
}
