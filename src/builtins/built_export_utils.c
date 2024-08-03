/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_export_utils.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 16:31:41 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/03 16:50:14 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*find_min_unflagged(t_env *env_list)
{
	t_env	*min_node;

	min_node = NULL;
	while (env_list)
	{
		if (!env_list->flag
			&& (!min_node || ft_strcmp(env_list->key, min_node->key) < 0))
			min_node = env_list;
		env_list = env_list->next;
	}
	return (min_node);
}

int	add_new_env_node(t_env **env_list, char *input)
{
	t_env	*new_node;

	new_node = ft_create_env_node(input);
	if (!new_node)
		return (MALERR);
	new_node->next = *env_list;
	*env_list = new_node;
	return (0);
}

int	ft_create_set_env_value(t_env *env, char *value, char *input)
{
	ft_free_string(&env->value);
	env->value = ft_strdup(value);
	if (!env->value)
		return (MALERR);
	ft_free_string(&env->env);
	env->env = ft_strdup(input);
	if (!env->env)
		return (MALERR);
	return (0);
}

int	ft_replace_env_value(t_env *env_list, char *input)
{
	char	*equal_sign;
	char	*new_value;
	char	*key;
	int		status;

	equal_sign = ft_strchr(input, '=');
	key = ft_substr(input, 0, ft_pos(input, '=')  - 1); //Check Malloc!!!
	// key = strndup(input, equal_sign - input); // illegal function
	if (!key)
		return (MALERR);
	new_value = ft_strdup(equal_sign + 1);
	if (!new_value)
		return (ft_free_string(&key), MALERR);
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			status = ft_create_set_env_value(env_list, new_value, input);
			return (ft_free_string(&key), ft_free_string(&new_value), status);
		}
		env_list = env_list->next;
	}
	return (ft_free_string(&key), ft_free_string(&new_value), 1);
}
