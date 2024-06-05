/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 10:35:35 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/05 22:24:54 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_token(char *str, t_token *token, int flag)
{
	int	len;

	len = 0;
	if (ft_lenword(str) > 0)
		len = ft_word(str, token);
	else if (ft_lenredirection(str) > 0)
		len = ft_redirection(str, token);
	else if (ft_lenpipe(str) > 0)
		len = ft_pipe(str, token);
	else if (ft_lensquote(str) > 0)
		len = ft_single_quote(str, token, flag);
	else if (ft_lendquote(str) > 0)
		len = ft_double_quote(str, token, flag);
	return (len);
}

void	ft_check_str(char *str, t_token *token)
{
	int		flag;
	int		len;
	int		i;

	flag = 1;
	i = 0;
	if (!str || !token)
		return ;
	while (str[i])
	{
		len = ft_token(&str[i], token, flag);
		if (len < 0)
			return ;	// TO_DO: Error & free
		else if (len > 0)
		{
			i += len;
			flag = 0;
			if (token->next)
				token = token->next;
		}
		else
		{
			i++;
			flag = 1;
		}
	}
}

void	my_func(char *str)
{
	t_token	*head;
	t_token	*token;

	token = ft_create_token();
	if (!token)
		return ;	// TO_DO: Error & free
	head = token;
	ft_check_str(str, token);
	while (token->next != NULL)
	{
		token = token->next;
	}
	token->word = NULL;
	token->type = T_EOF;
	ft_print_linked_list(head);
}

/*
Next steps:
1) Making notes for all the functions
2) Error handling (with a bigger struct)
3) Getting better sense of the complete assignment
4) Talk with Andres and Chriss what to do else? - What about the metacharacters??
*/

