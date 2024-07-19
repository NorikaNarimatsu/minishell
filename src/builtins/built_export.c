/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 16:31:41 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/19 21:09:35 by mdraper       ########   odam.nl         */
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
			&& (!min_node || strcmp(env_list->key, min_node->key) < 0))
			min_node = env_list;
		env_list = env_list->next;
	}
	return (min_node);
}

void	ft_print_sorted_env(t_env *env_list)
{
	t_env	*min_node;

	if (!env_list)
		return;
	ft_reset_env_flags(env_list);
	min_node = find_min_unflagged(env_list);
	while (min_node)
	{
		printf("declare -x %s", min_node->key);
		if (strchr(min_node->env, '='))
		{
			if (min_node->value)
				printf("=\"%s\"", min_node->value);
			else
				printf("=\"\"");
		}
		printf("\n");
		min_node->flag = true;
		min_node = find_min_unflagged(env_list);
	}
}

int	handle_export(t_env **env_list, char *input)
{
	char	*equal_sign;
	char	*key;
	t_env	*new_node;

	new_node = NULL;
	equal_sign = strchr(input, '=');
	if (equal_sign)
		key = strndup(input, equal_sign - input);
	else
		key = strdup(input);
	if (!key)
		return (EXIT_FAILURE);
	if (!is_valid_identifier(key))
	{
		ft_putstr_fd("export: not a valid identifier\n", 2);
		return (free(key), EXIT_FAILURE);
	}
	if (equal_sign)
	{
		if (is_exist_identifier(*env_list, key))
			ft_replace_env_value(*env_list, input);
		else
		{
			new_node = ft_create_env_node(input);
			if (!new_node)
			{
				free(key);
				return (EXIT_FAILURE);
			}
			new_node->next = *env_list;
			*env_list = new_node;
		}
	}
	else
	{
		if (!is_exist_identifier(*env_list, key))
		{
			new_node = ft_create_env_node(input);
			if (!new_node)
			{
				free(key);
				return (EXIT_FAILURE);
			}
			new_node->next = *env_list;
			*env_list = new_node;
		}
	}
	free(key);
	return (EXIT_SUCCESS);
}

int	ft_replace_env_value(t_env *env_list, const char *input)
{
	char	*equal_sign;
	char	*new_value;
	char	*key;

	equal_sign = strchr(input, '=');
	key = strndup(input, equal_sign - input);
	if (!key)
		return (EXIT_FAILURE);
	new_value = strdup(equal_sign + 1);
	if (!new_value)
	{
		free(key);
		return (EXIT_FAILURE);
	}
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
		{
			free(env_list->value);
			env_list->value = new_value;
			free(env_list->env);
			env_list->env = strdup(input);
			if (!env_list->env)
			{
				free(key);
				return (EXIT_FAILURE);
			}
			free(key);
			return (EXIT_SUCCESS);
		}
		env_list = env_list->next;
	}
	free(new_value);
	free(key);
	return (EXIT_FAILURE);
}

int	ft_export_builtin(char **input, t_env **env)
{
	int		i;
	int		status;

	i = 1;
	if (!input[i])
	{
		ft_print_sorted_env(*env);
		return (EXIT_SUCCESS);
	}
	else
	{
		status = EXIT_SUCCESS;
		while (input[i])
		{
			if (handle_export(env, input[i]) == EXIT_FAILURE)
				status = EXIT_FAILURE;
			i++;
		}
	}
	return (status);
}
