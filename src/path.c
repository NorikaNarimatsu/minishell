/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:37:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/05 18:13:34 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*search_path(char *filename)
{
	char	path[PATH_MAX];
	char	*value;
	char	*end;
	char	*dup;

	value = getenv("PATH");
	while (*value)
	{
		ft_bzero(path, PATH_MAX);
		end = ft_strchr(value, ':');
		if (end)
			strncpy(path, value, end - value); //todo
		else
			ft_strlcpy(path, value, PATH_MAX);
		ft_strlcat(path, "/", PATH_MAX);
		ft_strlcat(path, filename, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			dup = ft_strdup(path);
			if (dup == NULL)
				fatal_error("strdup");
			return (dup);
		}
		if (end == NULL)
			return (NULL);
		value = end + 1;
	}
	return (NULL);
}

void	validate_access(char *path, char *filename)
{
	if (path == NULL)
		error_exit(filename, "command not found", 127);
	if (access(path, F_OK) < 0)
		error_exit(filename, "command not found", 127);
}
