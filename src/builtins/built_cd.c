/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_cd.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/08 17:36:11 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/06 22:48:31 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_update_env_value(t_env *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			ft_free_string(&env_list->value);
			env_list->value = ft_strdup(value);
			if (!env_list->value)
				return (MALERR);
			ft_free_string(&env_list->env);
			env_list->env = ft_calloc(1, ft_strlen(key) + ft_strlen(value) + 2);
			if (!env_list->env)
				return (MALERR);
			ft_strcpy(env_list->env, key);
			ft_strcat(env_list->env, "=");
			ft_strcat(env_list->env, value);
			return (0);
		}
		env_list = env_list->next;
	}
	return (0);
}

static int	ft_update_pwd_and_owd(t_env **env_list)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_find_env_value(*env_list, "PWD");
	if (old_pwd)
	{
		old_pwd = ft_strdup(old_pwd);
		if (!old_pwd)
			return (MALERR);
		if (ft_update_env_value(*env_list, "OLDPWD", old_pwd) == MALERR)
			return (ft_free_string(&old_pwd), MALERR);
		ft_free_string(&old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("Error getting current working directory\n", 2);
		return (CWDERR);
	}
	else
	{
		if (ft_update_env_value(*env_list, "PWD", new_pwd) == MALERR)
			return (ft_free_string(&new_pwd), MALERR);
	}
	return (ft_free_string(&new_pwd), 0);
}

char	*ft_find_env_value(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

static int	cd_check_change(char *path, t_env **env)
{
	char	*oldpwd;

	if (!path || ft_strlen(path) == 0)
		return (ft_putstr_fd("cd: missing argument\n", 2), 1);
	if (ft_strcmp(path, "-") == 0)
	{
		oldpwd = ft_find_env_value(*env, "OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), 1);
		path = oldpwd;
		printf("%s\n", path);
	}
	if (is_valid_directory(path) == 0)
		return (ft_putstr_fd("cd: No such file or directory\n", 2), 1);
	if (chdir(path) == -1)
		return (perror("cd"), CHDERR);
	return (ft_update_pwd_and_owd(env));
}

int	ft_cd_builtin(char **input, t_env **env)
{
	char	*path;
	char	*home_path;

	if (input[1] && input[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (1);
	}
	if (!input[1] || ft_strlen(input[1]) == 0)
	{
		home_path = ft_find_env_value(*env, "HOME");
		if (!home_path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
		path = home_path;
	}
	else
		path = input[1];
	return (cd_check_change(path, env));
}
