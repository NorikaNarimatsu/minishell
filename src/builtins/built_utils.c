/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/04 13:26:14 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/24 15:58:51 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (env)
	{
		printf("env: %s\n", env->env);
		printf("key: %s [%p]\n", env->key, env);
		printf("value: %s\n\n", env->value);
		env = env->next;
	}
	env = head;
}

bool	is_valid_identifier(char *input)
{
	int	i;

	i = 0;
	if (!input || !(ft_isalpha(input[i]) || input[i] == '_'))
		return (false);
	i++;
	while (input[i])
	{
		if (!ft_isalnum(input[i]) && input[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

bool	is_exist_identifier(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (true);
		env_list = env_list->next;
	}
	return (false);
}

int	is_valid_directory(char *path)
{
	struct stat	path_stat;
	int			is_valid;

	if (stat(path, &path_stat) != 0)
		return (0);
	is_valid = S_ISDIR(path_stat.st_mode);
	return (is_valid);
}
