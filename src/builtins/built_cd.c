/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:36:11 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/22 17:32:21 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_update_env_value(t_env *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (ft_strcmp(env_list->key, key) == 0)
		{
			free(env_list->value);
			env_list->value = ft_strdup(value);
			if (!env_list->value)
			{
				ft_putstr_fd("Memory allocation error\n", 2);
				exit(EXIT_FAILURE);
			}
			free(env_list->env);
			env_list->env = calloc(1, ft_strlen(key) + ft_strlen(value) + 2);
			if (!env_list->env)
			{
				ft_putstr_fd("Memory allocation error\n", 2);
				exit(EXIT_FAILURE);
			}
			ft_strcpy(env_list->env, key);
			ft_strcat(env_list->env, "=");
			ft_strcat(env_list->env, value);
			return ;
		}
		env_list = env_list->next;
	}
}

void	ft_update_pwd_and_owd(t_env **env_list)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = ft_find_env_value(*env_list, "PWD");
	if (old_pwd)
	{
		old_pwd = ft_strdup(old_pwd);
		if (!old_pwd)
		{
			ft_putstr_fd("Memory allocation error\n", 2);
			exit(EXIT_FAILURE);
		}
		ft_update_env_value(*env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		ft_putstr_fd("Error getting current working directory\n", 2);
		exit(EXIT_FAILURE);
	}
	else
		ft_update_env_value(*env_list, "PWD", new_pwd);
	free(new_pwd);
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

int	cd_check_change(char *path, t_env **env)
{
	char	*oldpwd;

	if (!path || ft_strlen(path) == 0)
		return (ft_putstr_fd("cd: missing argument\n", 2), EXIT_FAILURE);
	if (ft_strcmp(path, "-") == 0)
	{
		oldpwd = ft_find_env_value(*env, "OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), EXIT_FAILURE);
		path = oldpwd;
		printf("%s\n", path);
	}
	if (is_valid_directory(path) == 0)
		return (ft_putstr_fd("cd: No such file or directory\n", 2), EXIT_FAILURE);
	if (chdir(path) != 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	ft_update_pwd_and_owd(env);
	return (EXIT_SUCCESS);
}

int	ft_cd_builtin(char **input, t_env **env)
{
	char	*path;
	char	*home_path;

	if (input[2])
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (EXIT_FAILURE);
	}
	if (!input[1] || ft_strlen(input[1]) == 0)
	{
		home_path = ft_find_env_value(*env, "HOME");
		if (!home_path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
		path = home_path;
	}
	else
		path = input[1];
	return (cd_check_change(path, env));
}
