/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_token.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 21:54:23 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/05 22:00:13 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_word(char *str, t_token *token)
{
	int	len;

	if (!str)
		return (-1);
	len = ft_fill_word(str, token, ft_lenword);
	if (len < 0)
		return (len);
	if (ft_fill_type_and_next(token, T_WORD) == -1)
		return (-1);
	return (len);
}

int	ft_redirection(char *str, t_token *token)
{
	int	len;

	len = ft_fill_word(str, token, ft_lenredirection);
	if (len < 0)
		return (len);
	if (ft_fill_type_and_next(token, T_OPERATER) == -1)
		return (-1);
	return (len);
}

int	ft_pipe(char *str, t_token *token)
{
	int	len;

	len = ft_fill_word(str, token, ft_lenpipe);
	if (len < 0)
		return (len);
	if (ft_fill_type_and_next(token, T_OPERATER) == -1)
		return (-1);
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
		token->prev->word = ft_strjoin_gnl(token->prev->word, token->word);
		return (free(token->word), len);
	}
	if (ft_fill_type_and_next(token, T_WORD) == -1)
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
		token->prev->word = ft_strjoin_gnl(token->prev->word, token->word);
		return (free(token->word), len);
	}
	if (ft_fill_type_and_next(token, T_WORD) == -1)
		return (-1);
	return (len);
}
