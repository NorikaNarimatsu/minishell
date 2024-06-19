/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/19 13:23:20 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_value2(char *line, t_env *env)
{
	t_env	*head;
	char	*key;
	int		i;
	int		j;
	char *leftover;
	char *result;

	i = 0;
	key = NULL;
	while (line[i] && line[i] != '$')
		i++;
	result = ft_substr(line, 0, i);
	printf("first result : %s\n", result);
	while (line[i])
	{
		j = 0;
		i++;
		while (line[i + j] && !ft_isspace(line[i + j]))
			j++;
		key = ft_substr(line, i, j);
		printf("key : %s\n", key);
		head = env;
		while (env)
		{
			printf("strcmp=%d [%s]\n", ft_strcmp(env->key, key), env->key);
			if (ft_strcmp(env->key, key) == 0)
			{
				printf("ITS A MATCH!!!\n");
				printf("%s -> %s\n", env->key, env->value);
				result = ft_strjoin(result, env->value);
				printf("result : %s\n", result);
			}
			env = env->next;
		}
		env = head;
		i = i + j;
		j = 0;
		while (line[i + j] && line[i + j] != '$')
			j++;
		leftover = ft_substr(line, i, j);
		printf("leftover : %s\n", leftover);
		result = ft_strjoin(result, leftover);
		printf("\n\nresult : %s\n\n", result);
		i = i + j;
	}
	printf("final result: %s\n", result);
	return (result);
}

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

int ft_expansion(char *line, t_env *env)
{
	// char	*key;

	// key = 
	get_key_value2(line, env);
	env = NULL;
	// while (env)
	// {
	// 	if (key == env->key)
	// 	{
	// 		key = env->value;
	// 	}
		
	// }
	return (0);
}
