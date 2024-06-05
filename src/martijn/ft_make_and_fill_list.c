/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_token.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:09:13 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/05 16:26:25 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_create_token(void)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	return (token);
}

int	ft_create_token_list(t_token *token)
{
	t_token	*new_token;

	new_token = ft_create_token();
	if (!new_token)
		return (-1);
	token->next = new_token;
	new_token->prev = token;
	return (0);
}

int	ft_fill_type_and_next(t_token *token, enum e_token type)
{
	if (ft_create_token_list(token) == -1)
		return (-1);
	token->type = type;
	token = token->next;
	return (0);
}

int	ft_fill_word(char *str, t_token *token, int (*strlen_func)(char *))
{
	int	len;

	len = strlen_func(str);
	if (len > 0)
	{
		token->word = (char *)ft_calloc(len + 1, sizeof(char));
		if (!token->word)
			return (-1);
		ft_strlcpy(token->word, str, len + 1);
	}
	return (len);
}
