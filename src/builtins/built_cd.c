/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 17:36:11 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/15 14:13:11 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the function to update the node in env linked list
// based on the given key and value
void	update_env_value(t_env *env_list, char *key, char *value)
{
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
		{
			free(env_list->value);
			env_list->value = strdup(value);
			if (!env_list->value)
				; // TODO, strdup
			free(env_list->env);
			env_list->env = malloc(strlen(key) + 1 + strlen(value) + 1);
			if (!env_list)
				; // TODO, malloc
			if (env_list->env)
			{
				strcpy(env_list->env, key);
				strcat(env_list->env, "=");
				strcat(env_list->env, value);
			}
			return ;
		}
		env_list = env_list->next;
	}
}

// This is the function to update pwd and oldpwd,
// when cd (builtin) is executed
void	update_pwd_and_owd(t_env *env_list)
{
	char	*old_pwd;
	char	*new_pwd;

	old_pwd = NULL;
	while (env_list)
	{
		if (strcmp(env_list->key, "PWD") == 0)
		{
			old_pwd = strdup(env_list->value);
			if (!old_pwd)
				; // TODO, strdup
			break ;
		}
		env_list = env_list->next;
	}
	if (old_pwd)
	{
		update_env_value(env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
		; //TODO getcwd
	else
	{
		update_env_value(env_list, "PWD", new_pwd);
		free(new_pwd);
	}
}

// This is the function to find the value (char *) of
// given key in env linked list
char	*find_env_value(t_env *env_list, char *key)
{
	while (env_list)
	{
		if (strcmp(env_list->key, key) == 0)
			return (env_list->value);
		env_list = env_list->next;
	}
	return (NULL);
}

int	cd_check_change(char *path, t_env *env)
{
	char	*oldpwd;

	if (!path || strlen(path) == 0)
		return (ft_putstr_fd("cd: missing argument\n", 2), EXIT_FAILURE);
	if (strcmp(path, "-") == 0)
	{
		oldpwd = find_env_value(env, "OLDPWD");
		if (!oldpwd)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), EXIT_FAILURE);
		path = oldpwd;
		printf("%s\n", path);
	}
	if (is_valid_directory(path) == 0)
		return (ft_putstr_fd("cd: no such file or directory\n", 2), EXIT_FAILURE);
	if (chdir(path) != 0)
		return (perror("cd"), EXIT_FAILURE); //TODO
	update_pwd_and_owd(env);
	return (0);
}

// This is the function to execute cd
// return 0 with success,1 fail.
int	cd_builtin(char **input, t_env *env)
{
	char	*path;
	char	*home_path;

	if (input[2])
		return (ft_putstr_fd("cd: too many arguments\n", 2), EXIT_FAILURE);
	if (!input[1] || strlen(input[1]) == 0)
	{
		home_path = find_env_value(env, "HOME");
		if (!home_path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), EXIT_FAILURE);
		path = home_path;
	}
	else
		path = input[1];
	return (cd_check_change(path, env));
}
