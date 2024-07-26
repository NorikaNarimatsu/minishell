/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_convert.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 16:05:34 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/26 16:55:15 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_env_to_array(t_env *env_list)
{
	int		count;
	char	**env_array;
	t_env	*temp;
	int		i;

	count = 0;
	temp = env_list;
	while (temp)
	{
		count++;
		temp = temp->next;
	}
	env_array = calloc(sizeof(char *), (count + 1));
	if (!env_array)
		return (NULL);
	temp = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i++] = temp->env;
		temp = temp->next;
	}
	env_array[count] = NULL;
	return (env_array);
}
