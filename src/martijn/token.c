/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 10:35:35 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/06 16:39:06 by mdraper       ########   odam.nl         */
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

void	ft_check_str(char *str, t_shell *shell)
{
	int		len;
	int		i;

	shell->token_flag = 1;
	i = 0;
	if (!str || !shell || !shell->ll_token)
		return ;
	while (str[i])
	{
		len = ft_token(&str[i], shell->ll_token, shell->token_flag);
		if (len < 0)
			return ;	// TO_DO: Error & free
		else if (len > 0)
		{
			i += len;
			shell->token_flag = 0;
			if (shell->ll_token->next)
				shell->ll_token = shell->ll_token->next;
		}
		else
		{
			i++;
			shell->token_flag = 1;
		}
	}
}

void	my_func(char *str, t_shell *shell)
{
	// t_token	*head;

	shell->ll_token = ft_create_token();
	if (!shell->ll_token)
		return ;	// TO_DO: Error & free
	// head = shell->ll_token;
	ft_check_str(str, shell);
	while (shell->ll_token->prev != NULL)
	{
		shell->ll_token = shell->ll_token->prev;
	}
	// shell->ll_token->word = NULL;
	// shell->ll_token->type = T_EOF;
	ft_print_linked_list(shell->ll_token);
	// shell->ll_token = head;
	ft_free_t_token(shell->ll_token);
}

/*
Next steps:
1) Making notes for all the functions
2) Error handling (with a bigger struct)
3) Getting better sense of the complete assignment
4) Talk with Andres and Chriss what to do else? - What about the metacharacters??
*/

