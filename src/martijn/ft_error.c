/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 14:08:28 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/06 16:04:04 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"





char *errdescr[] = {
	"No Errors",
	"Malloc error: No memory to allocate\n"
	"Syntax error: Unterminated quoted string\n"
};

void	get_errdescr(enum e_errno error)
{
	int	index;

	index = -error;
	printf("error number: %d\n", error);
	if (error >= 0)
		return ;
	ft_putstr_fd(errdescr[index], 2);
}

void	ft_free_t_token(t_token	*ll_token)
{
	t_token	*current;
	t_token	*next;

	current = ll_token;
	if (!ll_token)
		return ;
	while (current->next != NULL)
	{
		next = current->next;
		free(current);
		current = NULL;
		current = next;
	}
}
