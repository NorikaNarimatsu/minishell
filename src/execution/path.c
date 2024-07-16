/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:28:58 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/16 09:26:46 by nnarimat         ###   ########.fr       */
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
		end = strchr(value, ':');
		if (end)
			strncpy(path, value, end - value);
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			dup = ft_strdup(path);
			if (dup == NULL)
				ft_fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	ft_validate_access(char *path, char *filename)
{
	if (path == NULL)
		error_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		error_exit(filename, "command not found", 127);
}
