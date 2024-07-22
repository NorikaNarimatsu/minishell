/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:21:39 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/20 17:51:15 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env_builtin(char **input, t_env *env)
{
	t_env	*current;

	if (input[1])
	{
		ft_putstr_fd("env: No such file or directory\n", 2);
		return (127);
	}
	current = env;
	while (current)
	{
		if (current->value)
			printf("%s\n", current->env);
		current = current->next;
	}
	return (EXIT_SUCCESS);
}
