/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_error2.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 16:00:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/03 22:18:41 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_fd(int **fd)
{
	if (!fd || !*fd)
		return ;
	free(*fd);
	*fd = NULL;
}

void	ft_free_pid(pid_t **pid)
{
	if (!pid || !*pid)
		return ;
	free(*pid);
	*pid = NULL;
}

void	ft_free_env_node(t_env **node)
{
	if (node && *node)
	{
		ft_free_string(&(*node)->env);
		ft_free_string(&(*node)->key);
		ft_free_string(&(*node)->value);
		free(*node);
		*node = NULL;
	}
}

void	ft_free_env_list(t_env **current)
{
	t_env	*next_node;

	while (*current)
	{
		next_node = (*current)->next;
		ft_free_env_node(current);
		*current = next_node;
	}
}
