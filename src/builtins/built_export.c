/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_export.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 16:31:41 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/03 22:47:54 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_print_sorted_env(t_env *env_list)
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

static int	validate_and_extract_key(char *input, char **key, char **equal_sign)
{
	*equal_sign = ft_strchr(input, '=');
	if (*equal_sign)
		*key = ft_substr(input, 0, ft_pos(input, '=') - 1);
	else
		*key = ft_strdup(input);
	if (!*key)
		return (MALERR);
	if (is_valid_identifier(*key) == false)
	{
		ft_putstr_fd("export: not a valid identifier\n", STDERR_FILENO);
		ft_free_string(key);
		return (1);
	}
	return (0);
}

static int	handle_export(t_env **env_list, char *input)
{
	char	*equal_sign;
	char	*key;
	int		status;

	if (input[0] == '#')
		return (ft_print_sorted_env(*env_list), 0);
	status = validate_and_extract_key(input, &key, &equal_sign);
	if (status == MALERR || status == 1)
		return (ft_free_string(&key), status);
	if (equal_sign)
	{
		if (is_exist_identifier(*env_list, key) == true)
			status = ft_replace_env_value(*env_list, input);
		else
			status = add_new_env_node(env_list, input);
	}
	else
	{
		if (is_exist_identifier(*env_list, key) == false)
			status = add_new_env_node(env_list, input);
	}
	return (ft_free_string(&key), status);
}

int	ft_export_builtin(char **input, t_env **env)
{
	int		i;
	int		temp;
	int		status;

	temp = 0;
	status = 0;
	i = 1;
	if (!input[i])
	{
		ft_print_sorted_env(*env);
		return (0);
	}
	while (input[i])
	{
		temp = handle_export(env, input[i]);
		if (temp == MALERR)
			return (MALERR);
		else if (temp == 1)
			status = 1;
		i++;
	}
	return (status);
}
