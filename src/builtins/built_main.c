/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:49:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/17 19:20:51 by nnarimat         ###   ########.fr       */
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

int	ft_execute_builtin(t_shell *shell, t_exec *exec, t_env **env)
{
	if (ft_strcmp(exec->word[0], "echo") == 0)
		return (ft_echo_builtin(exec->word));
	else if (ft_strcmp(exec->word[0], "env") == 0)
		return (ft_env_builtin(exec->word, *env));
	else if (ft_strcmp(exec->word[0], "export") == 0)
		return (ft_export_builtin(exec->word, env));
	else if (ft_strcmp(exec->word[0], "unset") == 0)
		return (ft_unset_builtin(exec->word, env));
	else if (ft_strcmp(exec->word[0], "pwd") == 0)
		return (ft_pwd_builtin(exec->word, *env));
	else if (ft_strcmp(exec->word[0], "cd") == 0)
		return (ft_cd_builtin(exec->word, env));
	else if (ft_strcmp(exec->word[0], "exit") == 0)
		return (ft_exit_builtin(exec->word, shell));
	return (0);
}
