/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/26 23:37:56 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_position(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	ft_get_temp(char *line, t_expan *expanding)
{
	int		i;

	i = ft_get_position(line);
	expanding->temp = ft_substr(line, 0, i);
	if (!expanding->temp)
	{
		expanding->malloc_error = 1;
		return (MALERR);
	}
	if (i == (int)ft_strlen(line))
		expanding->need_to_expand = 0;
	else
		expanding->need_to_expand = 1;
	expanding->len = i;
	return (0);
}

char	*ft_get_new_string(char *str1, int malloc_flag_str1, char *str2, int malloc_flag_str2)
{
	char	*result;

	if (ft_strlen(str1) > 0 && ft_strlen(str2) > 0)
		result = ft_strjoin(str1, str2);
	else if (ft_strlen(str1) == 0 && ft_strlen(str2) > 0)
		result = ft_strdup(str2);
	else if (ft_strlen(str2) == 0)
		result = ft_strdup(str1);
	if (malloc_flag_str1 == 1)
		ft_free_string(&str1);
	if (malloc_flag_str2 == 1)
		ft_free_string(&str2);
	if (!result)
		return (NULL);
	return (result);
}

int	ft_strlen_dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

int	ft_get_env_edgecases(t_expan *expanding)
{
	if (ft_strlen_dollar_sign(expanding->key) == 0 && expanding->need_to_expand == 1)
	{
		ft_free_string(&expanding->key);
		expanding->key = ft_strdup("$");
		if (!expanding->key)
			return (MALERR);
		return (1);
	}
	else if (ft_strcmp(expanding->key, "$") == 0)
	{
		ft_free_string(&expanding->key);
		expanding->key = ft_itoa(getpid());
		if (!expanding->key)
			return (MALERR);
		return (1);
	}
	else if (ft_strcmp(expanding->key, "?") == 0)
	{
		ft_free_string(&expanding->key);
		expanding->key = ft_itoa(expanding->exit_status);
		if (!expanding->key)
			return (MALERR);
		return (1);
	}
	return (0);
}

int	ft_get_env(t_env *env, t_expan *expanding)
{
	int	value;

	expanding->key_malloc = 1;
	value = ft_get_env_edgecases(expanding);
	if (value < 0 || value == 1)
		return (value);
	while (env && expanding->need_to_expand == 1)
	{
		if (ft_strcmp(env->key, expanding->key) == 0)
		{
			ft_free_string(&expanding->key);
			expanding->key = ft_strdup(env->value);
			if (!expanding->key)
				return (MALERR);
			return (1);
		}
		env = env->next;
	}
	ft_free_string(&expanding->key);
	expanding->key_malloc = 0;
	return (0);
}

int	ft_get_key(char *line, t_expan *expanding)
{
	int		len;

	len = 1;
	while (line[len] && !ft_isspace(line[len]))
	{
		if (len == 1 && (line[len] == '$' || line[len] == '?'))
		{
			expanding->key = ft_substr(line, 1, len);
			if (!expanding->key)
				return (MALERR);
			expanding->len = 2;
			return (0);
		}
		len++;
	}
	expanding->key = ft_substr(line, 1, len);
	if (!expanding->key && len > 1)
	{
		expanding->malloc_error = 1;
		return (MALERR);
	}
	expanding->len = len;
	return (0);
}

// char	*get_key_value2(char *line, t_env *env)
// {
// 	t_env	*head;
// 	char	*key;
// 	int		i;
// 	int		j;
// 	char	*leftover;
// 	char	*result;

// 	i = 0;
// 	key = NULL;
// 	while (line[i] && line[i] != '$')
// 		i++;
// 	result = ft_substr(line, 0, i);
// 	printf("first result: %s\n", result);
// 	while (line[i])
// 	{
// 		j = 0;
// 		i++;
// 		while (line[i + j] && !ft_isspace(line[i + j]))
// 			j++;
// 		key = ft_substr(line, i, j);
// 		printf("key : %s\n", key);
// 		head = env;
// 		while (env)
// 		{
// 			printf("strcmp=%d [%s]\n", ft_strcmp(env->key, key), env->key);
// 			if (ft_strcmp(env->key, key) == 0)
// 			{
// 				printf("ITS A MATCH!!!\n");
// 				printf("%s -> %s\n", env->key, env->value);
// 				result = ft_strjoin(result, env->value);
// 				printf("result: %s\n", result);
// 			}
// 			env = env->next;
// 		}
// 		env = head;
// 		i = i + j;
// 		j = 0;
// 		while (line[i + j] && line[i + j] != '$')
// 			j++;
// 		leftover = ft_substr(line, i, j);
// 		printf("leftover : %s\n", leftover);
// 		result = ft_strjoin(result, leftover);
// 		printf("\n\nresult : %s\n\n", result);
// 		i = i + j;
// 	}
// 	printf("final result: %s\n", result);
// 	return (result);
// }

// char	*get_key_value(char *line, t_env *env)
// {
// 	t_env	*head;
// 	char	*key;
// 	char	*line2;
// 	int		flag;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	flag = 0;
// 	key = NULL;
// 	while (line[i])
// 	{
// 		if (line[i] == '$') // what if $name is wrong?
// 		{
// 			printf("Here we have to take key value! [%d - %c]\n", i, line[i]);
// 			j = 0;
// 			if (flag == 0)
// 			{
// 				line2 = ft_substr(line, 0, i);
// 				flag = 1;
// 			}
// 			i++;
// 			while (line[i + j] && !ft_isspace(line[i + j]))
// 			{
// 				printf("%c", line[i + j]);
// 				j++;
// 			}
// 			printf("\n\n");
// 			key = ft_substr(line, i, j);
// 			printf("key = %s\n", key);
// 			head = env;
// 			while (env)
// 			{
// 				// printf("strcmp = %d [%s]\n", ft_strcmp(env->key, key), env->key);
// 				if (ft_strcmp(env->key, key) == 0)
// 				{
// 					printf("ITS A MATCH!!!\n");
// 					printf("%s -> %s\n", env->key, env->value);
// 					line2 = ft_gnl_strjoin(line2, env->value);
// 					printf("line2=%s\n", line2);
// 					// ft_strdup();
// 				}
// 				env = env->next;
// 			}
// 			env = head;
// 			i += j;
// 		}
// 		i++;
// 	}
// 	return (key);
// }

t_expan *ft_create_expansion(void)
{
	t_expan *expansion;

	expansion = ft_calloc(1, sizeof(t_expan));
	if (!expansion)
		return (NULL);
	ft_bzero(expansion, sizeof(t_expan));
	return (expansion);
}

int	ft_expansion(char *line, t_env *env, t_expan *expanding)
{
	int		pos;

	if (ft_get_position(line) == (int)ft_strlen(line))
		return (0);
	pos = 0;
	expanding->expan_malloc = 0;
	while (line[pos])
	{
		if (ft_get_temp(&line[pos], expanding) < 0)
			return (MALERR);
		pos += expanding->len;
		if (ft_get_key(&line[pos], expanding) < 0)
			return (MALERR);
		pos += expanding->len;
		if (ft_get_env(env, expanding) < 0) // if 0, means not found. By return 1, it means it found something
			return (MALERR);
		expanding->temp = ft_get_new_string(expanding->temp, 1, expanding->key, expanding->key_malloc);
		if (!expanding->temp)
			return (MALERR);
		expanding->expanded_line = ft_get_new_string(expanding->expanded_line, expanding->expan_malloc, expanding->temp, 1);
		if (!expanding->expanded_line)
			return (MALERR);
		expanding->expan_malloc = 1;
	}
	printf("\n\nexpanding->expanded_line = %s\n\n", expanding->expanded_line);
	return (0);
}

/*
Think about memory free!
*/
