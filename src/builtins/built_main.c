/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:49:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 14:09:53 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *command)
{
	if ((ft_strcmp(command, "echo") == 0)
		|| (ft_strcmp(command, "env") == 0)
		|| (ft_strcmp(command, "export") == 0)
		|| (ft_strcmp(command, "unset") == 0)
		|| (ft_strcmp(command, "pwd") == 0)
		|| (ft_strcmp(command, "cd") == 0)
		|| (ft_strcmp(command, "exit") == 0))
		return (true);
	else
		return (false);
}

int	ft_execute_builtin(t_exec *exec, t_env *env)
{
	char	**input;

	input = exec->word;
	if (ft_strcmp(input[0], "echo") == 0)
		return (ft_echo_builtin(input));
	else if (ft_strcmp(input[0], "env") == 0)
		return (ft_env_builtin(input, env), 0);
	else if (ft_strcmp(input[0], "export") == 0)
		return (ft_export_builtin(input, env), 0);
	else if (ft_strcmp(input[0], "unset") == 0)
		return (ft_unset_builtin(input, env), 0);
	else if (ft_strcmp(input[0], "pwd") == 0)
		return (ft_pwd_builtin(input, env), 0);
	else if (ft_strcmp(input[0], "cd") == 0)
		return (ft_cd_builtin(input, env), 0);
	else if (ft_strcmp(input[0], "exit") == 0)
		return (ft_exit_builtin(input), 0);
	return (-1);
}
