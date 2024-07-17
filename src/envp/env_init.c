/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 12:44:31 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/16 17:08:22 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env_node(t_env **node)
{
	if (node && *node)
	{
		free((*node)->env);
		(*node)->env = NULL;
		free((*node)->key);
		(*node)->key = NULL;
		free((*node)->value);
		(*node)->value = NULL;
		free(*node);
		*node = NULL;
	}
}

void	ft_free_env_list(t_env *current)
{
	t_env	*next_node;

	while (current)
	{
		next_node = current->next;
		ft_free_env_node(&current);
		current = next_node;
	}
}

void	ft_reset_env_flags(t_env *env_list)
{
	while (env_list)
	{
		env_list->flag = false;
		env_list = env_list->next;
	}
}

t_env	*ft_create_env_node(char *env_str)
{
	t_env	*new_node;
	char	*equal_sign;

	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return (NULL);
	new_node->env = strdup(env_str);
	if (!new_node->env)
		return (free(new_node), NULL);
	equal_sign = ft_strchr(env_str, '=');
	if (equal_sign != NULL)
	{
		new_node->key = strndup(env_str, equal_sign - env_str); // TODO create original
		new_node->value = ft_strdup(equal_sign + 1);
	}
	else
	{
		new_node->key = ft_strdup(env_str);
		new_node->value = NULL;
	}
	if (!new_node->key || (equal_sign && !new_node->value))
		return (ft_free_env_node(&new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_env	*ft_init_env(char **env)
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
		new_node = ft_create_env_node(env[i]);
		if (!new_node)
		{
			ft_free_env_list(head);
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

