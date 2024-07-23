/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_token.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 21:54:23 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/23 11:45:09 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word(char *str, t_token *token, int flag)
{
	int		len;

	len = ft_fill_word(str, token, ft_lenword);
	if (len == MALERR)
		return (MALERR);
	if (flag == 0)
	{
		token->prev->word = ft_gnl_strjoin(token->prev->word, token->word);
		ft_free_string(&token->word);
		if (!token->prev->word)
			return (MALERR);
	}
	else if (ft_create_new_and_fill_type(token, T_WORD) == MALERR)
		return (MALERR);
	return (len);
}

int	ft_redirection(char *str, t_token *token, int *flag)
{
	int	len;
	int	error;

	error = 0;
	len = ft_fill_word(str, token, ft_lenredirection);
	if (len == MALERR)
		return (MALERR);
	if (str[0] == '<' && len == 1)
		error = ft_create_new_and_fill_type(token, T_INPUT);
	else if (str[0] == '<' && len == 2)
		error = ft_create_new_and_fill_type(token, T_HEREDOC);
	else if (str[0] == '>' && len == 1)
		error = ft_create_new_and_fill_type(token, T_OUTPUT);
	else if (str[0] == '>' && len == 2)
		error = ft_create_new_and_fill_type(token, T_APPEND);
	if (error == MALERR)
		return (MALERR);
	*flag = 1;
	return (len);
}

int	ft_pipe(char *str, t_token *token, int *flag)
{
	int	len;

	len = ft_fill_word(str, token, ft_lenpipe);
	if (len == MALERR)
		return (MALERR);
	if (ft_create_new_and_fill_type(token, T_PIPE) == MALERR)
		return (MALERR);
	*flag = 1;
	return (len);
}

int	ft_single_quote(char *str, t_token *token, int flag)
{
	char	*strtrim;
	int		len;

	len = ft_fill_word(str, token, ft_lensquote);
	if (len == MALERR)
		return (MALERR);
	strtrim = ft_strtrim(token->word, "'");
	if (!strtrim)
		return (MALERR);
	ft_free_string(&token->word);
	token->word = strtrim;
	if (flag == 0)
	{
		token->prev->word = ft_gnl_strjoin(token->prev->word, token->word);
		ft_free_string(&token->word);
		if (!token->prev->word)
			return (MALERR);
	}
	else if (ft_create_new_and_fill_type(token, T_WORD) == MALERR)
		return (MALERR);
	return (len);
}

int	ft_double_quote(char *str, t_token *token, int flag)
{
	char	*strtrim;
	int		len;

	len = ft_fill_word(str, token, ft_lendquote);
	if (len == MALERR)
		return (MALERR);
	strtrim = ft_strtrim(token->word, "\"");
	if (!strtrim)
		return (MALERR);
	ft_free_string(&token->word);
	token->word = strtrim;
	if (flag == 0)
	{
		token->prev->word = ft_gnl_strjoin(token->prev->word, token->word);
		ft_free_string(&token->word);
		if (!token->prev->word)
			return (MALERR);
	}
	else if (ft_create_new_and_fill_type(token, T_WORD) == MALERR)
		return (MALERR);
	return (len);
}
