/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_tokenization.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 10:35:35 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/06 22:38:39 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_token(char *str, t_token *token, int *flag)
{
	int	len;

	len = 0;
	if (ft_lenword(str) > 0)
		len = ft_word(str, token, *flag);
	else if (ft_lenredirection(str) > 0)
		len = ft_redirection(str, token, flag);
	else if (ft_lenpipe(str) > 0)
		len = ft_pipe(str, token, flag);
	else if (ft_lensquote(str) > 0)
		len = ft_single_quote(str, token, *flag);
	else if (ft_lendquote(str) > 0)
		len = ft_double_quote(str, token, *flag);
	return (len);
}

static int	ft_check_str(char *str, t_token *ll_token, int *token_flag)
{
	int		len;
	int		i;

	i = 0;
	while (str[i])
	{
		len = ft_token(&str[i], ll_token, token_flag);
		if (len == MALERR)
			return (MALERR);
		else if (len > 0)
		{
			i += len;
			if (ll_token->type == T_WORD)
				*token_flag = 0;
			if (ll_token->next)
				ll_token = ll_token->next;
		}
		else
		{
			i++;
			*token_flag = 1;
		}
	}
	return (0);
}

int	ft_tokenization(t_shell *shell)
{
	t_token	*ll_token;

	if (!shell)
		return (MALERR);
	ll_token = ft_create_token();
	if (!ll_token)
		return (MALERR);
	if (ft_check_str(shell->line, ll_token, &shell->token_flag) == MALERR)
		return (ft_free_t_token(&ll_token), MALERR);
	while (ll_token->prev != NULL)
		ll_token = ll_token->prev;
	if (ft_transfer_for_exec(ll_token, shell->execution) == MALERR)
		return (ft_free_t_token(&ll_token), MALERR);
	ft_free_t_token(&ll_token);
	return (0);
}
