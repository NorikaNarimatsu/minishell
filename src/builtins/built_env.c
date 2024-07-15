/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:21:39 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/15 14:08:38 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// This is the Function to execute env
// Only printing out if they have value
int	env_builtin(char **input, t_env *env)
{
	t_env	*current;

	if (input[1])
	{
		printf("Too much argument\n");
		return (EXIT_SUCCESS);
	}
	current = env;
	while (current)
	{
		if (current->value)
			ft_putendl_fd(current->env, 1);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
