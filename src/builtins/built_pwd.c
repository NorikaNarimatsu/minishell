/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_pwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:49:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 19:10:15 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd_builtin(char **input, t_env *env)
{
	t_env	*current;

	(void) input;
	current = env;
	while (current)
	{
		if (strcmp(current->key, "PWD") == 0)
		{
			ft_putendl_fd(current->value, 1);
			return (EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_FAILURE);
}
