/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:41 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/22 16:49:07 by nnarimat         ###   ########.fr       */
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

// int	validate_and_extract_key(char *input, char **key, char **equal_sign)
// {
// 	*equal_sign = ft_strchr(input, '=');
// 	if (*equal_sign)
// 		*key = strndup(input, *equal_sign - input); // martijn
// 	else
// 		*key = ft_strdup(input);
// 	if (!*key)
// 		return (EXIT_FAILURE);
// 	if (!is_valid_identifier(*key))
// 	{
// 		ft_putstr_fd("export: not a valid identifier\n", 2);
// 		free(*key);
// 		return (EXIT_FAILURE);
// 	}
// 	return (EXIT_SUCCESS);
// }

int	add_new_env_node(t_env **env_list, char *input, char *key)
{
	t_env	*new_node;

	new_node = ft_create_env_node(input);
	if (!new_node)
	{
		free(key);
		return (EXIT_FAILURE);
	}
	new_node->next = *env_list;
	*env_list = new_node;
	free(key);
	return (EXIT_SUCCESS);
}

int	ft_create_set_env_value(t_env *env, char *value, char *input)
{
	free(env->value);
	env->value = ft_strdup(value);
	if (!env->value)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		return (EXIT_FAILURE);
	}
	free(env->env);
	env->env = ft_strdup(input);
	if (!env->env)
	{
		ft_putstr_fd("Memory allocation error\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_replace_env_value(t_env *env_list, char *input)
{
	char	*equal_sign;
	char	*new_value;
	char	*key;
	int		status;

	equal_sign = ft_strchr(input, '=');
	key = strndup(input, equal_sign - input);
	if (!key)
		return (EXIT_FAILURE);
	new_value = ft_strdup(equal_sign + 1);
	if (!new_value)
		return (free(key), EXIT_FAILURE);
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			status = ft_create_set_env_value(env_list, new_value, input);
			return (free(key), free(new_value), status);
		}
		env_list = env_list->next;
	}
	return (free(new_value), free(key), EXIT_FAILURE);
}
