/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_init.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 12:44:31 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/06/18 16:15:07 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (equal_sign)
	{
		new_node->key = strndup(env_str, equal_sign - env_str);
		new_node->value = strdup(equal_sign + 1);
	}
	else
	{
		new_node->key = strdup(env_str);
		new_node->value = NULL;
	}
	if (!new_node->key || (!new_node->value && equal_sign))
		return (free(new_node->env), free(new_node->key), free(new_node->value), free(new_node), NULL);
	new_node->next = NULL;
	return (new_node);
}

t_env	*init_env(char **env)
{
	t_env	*head;
	t_env	*current;
	t_env	*new_node;

	head = NULL;
	current = NULL;
	while (*env)
	{
		new_node = create_env_node(*env);
		if (!new_node)
		{
			while (head)
			{
				current = head->next;
				// free(new_node->env), free(new_node->key), free(new_node->value), free(new_node);
				head = current;
			}
			return (NULL);
		}
		if (!head)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		env++;
	}
	return (head);
}
