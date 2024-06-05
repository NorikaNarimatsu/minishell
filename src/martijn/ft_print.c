/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:38:08 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/05 15:39:01 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_print_linked_list(t_token *token)
{
	t_token	*head;

	head = token;
	while (token->next != NULL)
	{
		printf("Prev: %p\t", token->prev);
		printf("Curr: %p\t", token);
		printf("Next: %p\t", token->next);
		printf("\tstr= %s", token->word);
		printf(" [%d]\n", token->type);
		token = token->next;
	}
	token = head;
}
