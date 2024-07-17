/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:41:43 by mdraper           #+#    #+#             */
/*   Updated: 2024/07/16 20:09:26 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_expan	*ft_create_expansion(void)
{
	t_expan	*expansion;

	expansion = ft_calloc(1, sizeof(t_expan));
	if (!expansion)
		return (NULL);
	return (expansion);
}

void	ft_free_expansion(t_expan *exp)
{
	// printf("exp->exp_line = %s\n", exp->exp_line); // have to delete this later!
	ft_free_string(&(exp->temp));
	ft_free_string(&(exp->key));
	// ft_free_string(&(exp->exp_line));
}
