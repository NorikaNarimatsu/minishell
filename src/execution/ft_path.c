/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:28:58 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/22 16:42:06 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_search_path(char *filename, t_env *env)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = ft_find_env_value(env, "PATH");
	while (*value)
	{
		bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			strncpy(path, value, end - value); // strlcpy does not work!
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			dup = ft_strdup(path);
			if (dup == NULL)
			{
				ft_putstr_fd("strdup error", 2);
				exit(EXIT_FAILURE);
			}
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	ft_validate_access(char *path, char *filename, t_shell *shell)
{
	(void) filename;
	if (path == NULL)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		shell->exit_status = 127;
		exit(shell->exit_status);
	}
	if (access(path, F_OK) < 0)
	{
		ft_putstr_fd("minishell: command not found\n", 2);
		shell->exit_status = 127;
		exit(shell->exit_status);
	}
}
