/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:38:07 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/05 22:19:46 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_valid_envkey_idx(t_data *data, char *envkey)
{
	int	i;
	int	index;
	int	len;

	i = 0;
	while (envkey[i])
	{
		if (!(('A' <= envkey[i] && envkey[i] <= 'Z') || envkey[i] == '_'))
			return (-1);
		i++;
	}
	index = 0;
	len = ft_strlen(envkey);
	while (data->env[index])
	{
		if (strncmp(data->env[index], envkey, len) == 0)
			return (index);
		index ++;
	}
	return (-1);
}

int	unset_builtin(char **args, t_data *data)
{
	int	index;

	if (!args[2])
	{
		printf("not enough arguments\n");
		return (EXIT_FAILURE);
	}
	index = is_valid_envkey_idx(data, args[2]);
	printf("path to delete is %s\n", data->env[index]);
	if (index < 0)
	{
		printf("not a valid identifier\n");
		return (EXIT_FAILURE);
	}
	else
	{
		if (remove_env_var(data, index))
			return (EXIT_SUCCESS);
		else
			return (EXIT_FAILURE);
	}
}
https://github.com/fraqioui/minishell?tab=readme-ov-file#Builtins





// /* realloc_env_vars:
// *	Reallocates memory for the global variable g_env_vars.
// *
// *	Returns a pointer to the new environment variables
// *	or NULL in case of a memory allocation error.
// */


// /* remove_env_var:
// *	Removes the variable at the given index from the
// *	environment variables.
// *
// *	Returns 1 if the removal was successful, 0 if case
// *	of an invalid index or a memory allocation error.
// */

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
// 		free(data->env[i]);
// 		i++;
// 	}
// 	free(data->env);
// 	return (new_env);
// }

// bool	remove_env_var(t_data *data, int index)
// {
// 	int	count;

// 	free(data->env[index]);
// 	count = index;
// 	while (data->env[index + 1])
// 	{
// 		data->env[index] = ft_strdup(data->env[index + 1]);
// 		free(data->env[index + 1]);
// 		count++;
// 		index++;
// 	}
// 	data->env = realloc_env_vars(data, count);
// 	if (!data->env)
// 		return (false);
// 	return (true);
// }