/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:29:44 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/15 11:32:58 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Function to count the number of commands
int	count_command(t_exec *exec)
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

void	fatal_error(char *message)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", message);
	exit(1);
}

void	error_exit(char *location, char *message, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, message);
	exit(status);
}

char	**env_list_to_array(t_env *env_list)
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
	env_array = malloc(sizeof(char *) * (count + 1));
	if (!env_array)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	temp = env_list;
	i = 0;
	while (i < count)
	{
		env_array[i] = temp->env;
		temp = temp->next;
		i++;
	}
	env_array[count] = NULL;
	return (env_array);
}
