/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_utils.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/13 16:29:44 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/25 18:29:05 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_command(t_exec *exec)
{
	int	count;

	count = 0;
	while (exec)
	{
		count++;
		exec = exec->pipe;
	}
	return (count);
}

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
