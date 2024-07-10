/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_token.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 21:54:23 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/10 18:02:28 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_word(char *str, t_token *token)
{
	int	len;

	len = ft_fill_word(str, token, ft_lenword);
	if (len < 0)
		return (len);
	if (ft_create_new_and_fill_type(token, T_WORD) == MALERR)
		return (MALERR);
	return (len);
}

int	ft_redirection(char *str, t_token *token)
{
	int	len;
	int	error;

	len = ft_fill_word(str, token, ft_lenredirection);
	if (len < 0)
		return (len);
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
	return (len);
}

int	ft_pipe(char *str, t_token *token)
{
	int	len;

	len = ft_fill_word(str, token, ft_lenpipe);
	if (len < 0)
		return (len);
	if (ft_create_new_and_fill_type(token, T_PIPE) == MALERR)
		return (MALERR);
	return (len);
}

int	ft_single_quote(char *str, t_token *token, int flag)
{
	char	*strtrim;
	int		len;

	len = ft_fill_word(str, token, ft_lensquote);
	if (len < 0)
		return (len);
	strtrim = ft_strtrim(token->word, "'");
	if (!strtrim)
		return (-1);
	if (strtrim[0] == '\0')
		return (free(strtrim), free(token->word), len);
	free(token->word);
	token->word = strtrim;
	if (flag == 0)
	{
		token->prev->word = ft_gnl_strjoin(token->prev->word, token->word);
		free(token->word);
		token->word = NULL;
	}
	else if (ft_create_new_and_fill_type(token, T_WORD) == -1)
		return (-1);
	return (len);
}

int	ft_double_quote(char *str, t_token *token, int flag)
{
	char	*strtrim;
	int		len;

	len = ft_fill_word(str, token, ft_lendquote);
	if (len < 0)
		return (len);
	strtrim = ft_strtrim(token->word, "\"");
	if (!strtrim)
		return (-1);
	if (strtrim[0] == '\0')
		return (free(strtrim), free(token->word), len);
	free(token->word);
	token->word = strtrim;
	if (flag == 0)
	{
		token->prev->word = ft_gnl_strjoin(token->prev->word, token->word);
		free(token->word);
		token->word = NULL;
	}
	else if (ft_create_new_and_fill_type(token, T_WORD) == -1)
		return (-1);
	return (len);
}
