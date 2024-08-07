/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_path.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/13 16:28:58 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/07 23:58:22 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_path(char *path, const char *value, const char *filename)
{
	char	*end;

	end = ft_strchr(value, ':');
	bzero(path, PATH_MAX);
	if (end)
		ft_strlcpy(path, value, end - value + 1);
	else
		ft_strlcpy(path, value, PATH_MAX);
	ft_strlcat(path, "/", PATH_MAX);
	ft_strlcat(path, filename, PATH_MAX);
}

static char	*try_path(const char *path)
{
	char	*dup;

	if (access(path, X_OK) == 0)
	{
		dup = ft_strdup(path);
		if (!dup)
		{
			perror("ft_strdup");
			exit(EXIT_FAILURE);
		}
		return (dup);
	}
	return (NULL);
}

static char	*ft_search_path(char *filename, t_env *env)
{
	char	path[PATH_MAX];
	char	*value;
	char	*result;

	value = ft_find_env_value(env, "PATH");
	result = NULL;
	while (*value)
	{
		build_path(path, value, filename);
		result = try_path(path);
		if (result)
			return (result);
		value = ft_strchr(value, ':');
		if (!value)
			break ;
		value++;
	}
	return (NULL);
}

char	*ft_path_error(t_exec *exec, t_env *env, char *path)
{
	struct stat	statbuf;

	if (ft_strchr(path, '/') == NULL)
		path = ft_search_path(path, env);
	if (stat(path, &statbuf) == 0)
	{
		if (S_ISDIR(statbuf.st_mode))
			ft_error_exit(" Is a directory\n", 126);
		else if (access(path, X_OK) != 0)
			ft_error_exit(" Permission denied\n", 126);
	}
	else
	{
		if (ft_strchr(exec->word[0], '/') == NULL)
			ft_error_exit(" command not found\n", 127);
		else
			ft_error_exit(" No such file or directory\n", 127);
	}
	return (path);
}
