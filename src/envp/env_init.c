/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:44:31 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 13:42:37 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_env *node)
{
	if (node)
	{
		free(node->env);
		free(node->key);
		free(node->value);
		free(node);
	}
}

void	free_env_list(t_env *head)
{
	t_env	*current;
	t_env	*next_node;

	current = head;
	while (current)
	{
		next_node = current->next;
		free_env_node(current);
		current = next_node;
	}
}

void	reset_env_flags(t_env *env_list)
{
	while (env_list)
	{
		env_list->flag = false;
		env_list = env_list->next;
	}
}

t_env	*create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->env = strdup(env_str);
	if (!new_node->env)
		return (free(new_node), NULL);
	equal_sign = strchr(env_str, '=');
	if (equal_sign != NULL)
	{
		new_node->key = strndup(env_str, equal_sign - env_str);
		new_node->value = strdup(equal_sign + 1);
	}
	else
	{
		new_node->key = strdup(env_str);
		new_node->value = NULL;
	}
	if (!new_node->key || (equal_sign && !new_node->value))
		return (free_env_node(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;
	int		i;

	head = NULL;
	current = NULL;
	i = 0;
	while (env[i])
	{
		new_node = create_env_node(env[i]);
		if (!new_node)
		{
			free_env_list(head);
			return (NULL);
		}
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		i++;
	}
	return (head);
}

