/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:29:44 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/22 14:30:38 by nnarimat         ###   ########.fr       */
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
	{
		ft_putstr_fd("malloc error", 2);
		exit(EXIT_FAILURE);
	}
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
