/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:21:39 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 18:55:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// This is the Function to execute env
// Only printing out if they have value
int	ft_env_builtin(char **input, t_env *env)
{
	t_env	*current;

	if (input[1])
	{
		fprintf(stderr, "env: '%s': No such file or directory\n", input[1]);
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
