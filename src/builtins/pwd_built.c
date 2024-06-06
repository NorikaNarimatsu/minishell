/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:49:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/06 13:56:05 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_builtin(char **argv, t_data *data)
{
	t_env	*current;

	(void) argv;
	current = data->env_copy;
	while (current)
	{
		if (ft_strcmp(current->key, "PWD") == 0)
		{
			data->cwd = current->value;
			return (ft_putendl_fd(data->cwd, 1), EXIT_SUCCESS);
		}
		current = current->next;
	}
	return (EXIT_FAILURE);
}