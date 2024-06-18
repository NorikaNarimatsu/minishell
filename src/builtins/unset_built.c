/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:38:07 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/18 14:23:00 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


// bool	is_valid_env_var_key(char *var)
// {
// 	int	i;

// 	i = 0;
// 	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
// 		return (false);
// 	i++;
// 	while (var[i] && var[i] != '=')
// 	{
// 		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
// 			return (false);
// 		i++;
// 	}
// 	return (true);
// }


// static char	**realloc_env_vars(t_data *data, int size)
// {
// 	char	**new_env;
// 	int		i;

// 	new_env = ft_calloc(size + 1, sizeof * new_env);
// 	if (!new_env)
// 		return (NULL);
// 	i = 0;
// 	while (data->env[i] && i < size)
// 	{
// 		new_env[i] = ft_strdup(data->env[i]);
// 		free_ptr(data->env[i]);
// 		i++;
// 	}
// 	free(data->env);
// 	return (new_env);
// }

// bool	remove_env_var(t_data *data, int idx)
// {
// 	int	i;
// 	int	count;

// 	if (idx > env_var_count(data->env))
// 		return (false);
// 	free_ptr(data->env[idx]);
// 	i = idx;
// 	count = idx;
// 	while (data->env[i + 1])
// 	{
// 		data->env[i] = ft_strdup(data->env[i + 1]);
// 		free_ptr(data->env[i + 1]);
// 		count++;
// 		i++;
// 	}
// 	data->env = realloc_env_vars(data, count);
// 	if (!data->env)
// 		return (false);
// 	return (true);
// }

// int	get_env_var_index(t_env *env, char *key)
// {
// 	while (data)
// }

// int	unset_builtin(char **args, t_data *data)
// {
// 	int	i;
// 	int	idx;
// 	int	ret;

// 	ret = EXIT_SUCCESS;
// 	i = 2;
// 	while (args[i])
// 	{
// 			idx = get_env_var_index(data->env_copy, args[i]);
// 			if (idx != -1)
// 				remove_env_var(data, idx);
// 		}
// 		i++;
// 	}
// 	return (ret);
// }
