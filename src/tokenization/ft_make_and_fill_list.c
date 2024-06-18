/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_make_and_fill_list.c                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:09:13 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/11 17:59:52 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*ft_create_token(void)
{
	t_token	*token;

	token = ft_calloc(1, sizeof(t_token));
	if (!token)
		return (NULL);
	ft_bzero(token, sizeof(t_token));
	return (token);
}

t_exec	*ft_create_exec(void)
{
	t_exec	*execution;

	execution = ft_calloc(1, sizeof(t_exec));
	if (!execution)
		return (NULL);
	ft_bzero(execution, sizeof(t_exec));
	return (execution);
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

int	ft_create_new_and_fill_type(t_token *token, enum e_token type)
{
	if (ft_create_token_list(token) == -1)
		return (-1);
	token->type = type;
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
