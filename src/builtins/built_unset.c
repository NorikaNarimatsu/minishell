/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:23:32 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/16 09:29:03 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_env_var(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*previous;

	if (!env_list || !*env_list)
		return ;
	current = *env_list;
	previous = NULL;
	while (current)
	{
		if (strcmp(current->key, key) == 0)
		{
			if (previous)
				previous->next = current->next;
			else
				*env_list = current->next;
			ft_free_env_node(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset_builtin(char **input, t_env *env)
{
	int	i;

	i = 1;
	while (input[i])
	{
		unset_env_var(&(env), input[i]);
		i++;
	}
}
