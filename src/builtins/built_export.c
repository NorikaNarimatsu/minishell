/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:41 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/22 16:48:44 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_sorted_env(t_env *env_list)
{
	t_env	*min_node;

	if (!env_list)
		return ;
	ft_reset_env_flags(env_list);
	min_node = find_min_unflagged(env_list);
	while (min_node)
	{
		printf("declare -x %s", min_node->key);
		if (ft_strchr(min_node->env, '='))
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

int	validate_and_extract_key(char *input, char **key, char **equal_sign)
{
	int		i;

	i = 0;
	*equal_sign = ft_strchr(input, '=');
	if (*equal_sign)
		*key = strndup(input, *equal_sign - input);
	else
		*key = ft_strdup(input);
	if (!*key)
	{
		ft_putstr_fd("Memory allocation error\n", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	if (!is_valid_identifier(*key))
	{
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		free(*key);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	handle_export(t_env **env_list, char *input)
{
	char	*equal_sign;
	char	*key;
	int		status;

	status = validate_and_extract_key(input, &key, &equal_sign);
	if (status == EXIT_FAILURE)
		return (status);
	if (equal_sign)
	{
		if (is_exist_identifier(*env_list, key))
			status = ft_replace_env_value(*env_list, input);
		else
			status = add_new_env_node(env_list, input, key);
	}
	else
	{
		if (!is_exist_identifier(*env_list, key))
			status = add_new_env_node(env_list, input, key);
		else
			free(key);
	}
	return (status);
}

int	ft_export_builtin(char **input, t_env **env)
{
	int		i;
	int		status;

	status = EXIT_SUCCESS;
	i = 1;
	if (!input[i])
	{
		ft_print_sorted_env(*env);
		return (EXIT_SUCCESS);
	}
	while (input[i])
	{
		if (handle_export(env, input[i]) == EXIT_FAILURE)
			status = EXIT_FAILURE;
		i++;
	}
	return (status);
}
