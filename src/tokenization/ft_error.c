/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 14:08:28 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/10 12:18:40 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"





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

void	ft_free_string(char **str)
{
	if (!str | !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	ft_free_t_token(t_token	**ll_token)
{
	t_token	*current;
	t_token	*next;

	if (!ll_token | !*ll_token)
		return ;
	current = *ll_token;
	while (current)
	{
		next = current->next;
		ft_free_string(&(current->word));
		free(current);
		current = NULL;
		current = next;
	}
	*ll_token = NULL;
}
