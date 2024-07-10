/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 15:23:32 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 13:42:40 by nnarimat         ###   ########.fr       */
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
			free_env_node(current);
			return ;
		}
		previous = current;
		current = current->next;
	}
}

void	unset_builtin(char **input, t_shell *shell)
{
	int	i;

	i = 1;
	while (input[i])
	{
		unset_env_var(&(shell->env), input[i]);
		i++;
	}
}
