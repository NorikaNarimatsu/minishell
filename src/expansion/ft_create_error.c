/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_create_error.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/05 21:30:59 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expan	*ft_create_expansion(t_shell *shell, bool heredoc)
{
	t_expan	*expansion;

	expansion = ft_calloc(1, sizeof(t_expan));
	if (!expansion)
		return (NULL);
	if (heredoc == false)
		expansion->exit_status = shell->exit_status;
	return (expansion);
}

void	ft_free_small_expansion(t_expan *exp)
{
	ft_free_string(&(exp->temp));
	ft_free_string(&(exp->key));
}

void	ft_free_expansion(t_expan **exp)
{
	if (!exp | !*exp)
		return ;
	ft_free_string(&(*exp)->temp);
	ft_free_string(&(*exp)->key);
	ft_free_string(&(*exp)->exp_line);
	free(*exp);
	*exp = NULL;
}
