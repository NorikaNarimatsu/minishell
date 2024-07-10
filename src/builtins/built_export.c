/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:31:41 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 13:42:45 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_env_value(t_env *env_list, const char *input)
{
	char	*equal_sign;
	char	*new_value;
	char	*key;

	equal_sign = strchr(input, '=');
	key = strndup(input, equal_sign - input);
	if (!key)
		; // TODO
	new_value = strdup(equal_sign + 1);
	if (!new_value)
		; // TODO
	if (new_value)
	{
		while (env_list)
		{
			if (strcmp(env_list->key, key) == 0)
			{
				free(env_list->value);
				env_list->value = new_value;
				free(env_list->env);
				env_list->env = strdup(input);
				if (!env_list->env)
					; //TODO
				free(key);
				return ;
			}
			env_list = env_list->next;
		}
		free(new_value);
	}
	free(key);
}


void	handle_export(t_env **env_list, char *input)
{
	char	*equal_sign;
	char	*key;
	t_env	*new_node;

	new_node = NULL;
	equal_sign = strchr(input, '=');
	if (equal_sign)
		key = strndup(input, equal_sign - input);
	else
		key = strdup(input);
	if (!is_valid_identifier(key))
	{
		printf("export: `%s': not a valid identifier\n", input);
		free(key);
		return ;
	}
	if (equal_sign)
	{
		if (is_exist_identifier(*env_list, key))
			replace_env_value(*env_list, input);
		else
		{
			new_node = create_env_node(input);
			if (new_node)
			{
				new_node->next = *env_list;
				*env_list = new_node;
			}
		}
	}
	else
	{
		if (!is_exist_identifier(*env_list, key))
		{
			new_node = create_env_node(input);
			if (new_node)
			{
				new_node->next = *env_list;
				*env_list = new_node;
			}
		}
	}
	free(key);
}

t_env	*find_min_unflagged(t_env *env_list)
{
	t_env	*min_node;

	min_node = NULL;
	while (env_list)
	{
		if (!env_list->flag
			&& (!min_node || strcmp(env_list->key, min_node->key) < 0))
			min_node = env_list;
		env_list = env_list->next;
	}
	return (min_node);
}

void	print_env_list_sorted(t_env *env_list)
{
	t_env	*min_node;

	if (!env_list)
		return ;
	reset_env_flags(env_list);
	min_node = find_min_unflagged(env_list);
	while (min_node)
	{
		printf("declare -x %s", min_node->key);
		if (strchr(min_node->env, '='))
		{
			if (min_node->value)
				printf("=\"%s\"", min_node->value);
			else
				printf("=\"\"");
		}
		printf("\n");
		min_node->flag = true;
		min_node = find_min_unflagged(env_list);
	}
}

int	export_builtin(char **input, t_shell *shell)
{
	int		i;

	i = 1;
	if (!input[i])
	{
		print_env_list_sorted(shell->env);
		return (EXIT_SUCCESS);
	}
	else
	{
		while (input[i])
		{
			handle_export(&(shell->env), input[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

/*
nnarimat@f1r5s18:~$ export MARTIJN
nnarimat@f1r5s18:~$ export | grep MARTIJN
declare -x MARTIJN
nnarimat@f1r5s18:~$ env | grep MARTIJN
nnarimat@f1r5s18:~$ export MARTIJN=
nnarimat@f1r5s18:~$ export | grep MARTIJN
declare -x MARTIJN=""
nnarimat@f1r5s18:~$ env | grep MARTIJN
MARTIJN=
nnarimat@f1r5s18:~$

IF YOU WANT TO CHECK THE CD
void	print_env_list_sorted(t_env *env_list)
{
	t_env	*min_node;

	if (!env_list)
		return ;
	reset_env_flags(env_list);
	min_node = find_min_unflagged(env_list);
	while (min_node)
	{
		if (strcmp(min_node->key, "OLDPWD") == 0 || strcmp(min_node->key, "PWD") == 0)
		{
			printf("declare -x %s", min_node->key);
			if (strchr(min_node->env, '='))
			{
				if (min_node->value)
					printf("=\"%s\"", min_node->value);
				else
					printf("=\"\"");
			}
			printf("\n");
		}
		min_node->flag = true;
		min_node = find_min_unflagged(env_list);
	}
}
*/
