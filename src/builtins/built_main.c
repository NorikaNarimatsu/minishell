/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:49:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/16 09:25:21 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(char *command)
{
	if ((strcmp(command, "echo") == 0)
		|| (strcmp(command, "env") == 0)
		|| (strcmp(command, "export") == 0)
		|| (strcmp(command, "unset") == 0)
		|| (strcmp(command, "pwd") == 0)
		|| (strcmp(command, "cd") == 0)
		|| (strcmp(command, "exit") == 0))
		return (true);
	else
		return (false);
}


int	ft_execute_builtin(t_exec *exec, t_env *env)
{
	char	**input;

	input = exec->word;
	if (strcmp(input[0], "echo") == 0)
		return (ft_echo_builtin(input), 0);
	else if (strcmp(input[0], "env") == 0)
		return (ft_env_builtin(input, env), 0);
	else if (strcmp(input[0], "export") == 0)
		return (ft_export_builtin(input, env), 0);
	else if (strcmp(input[0], "unset") == 0)
		return (ft_unset_builtin(input, env), 0);
	else if (strcmp(input[0], "pwd") == 0)
		return (ft_pwd_builtin(input, env), 0);
	else if (strcmp(input[0], "cd") == 0)
		return (ft_cd_builtin(input, env), 0);
	else if (strcmp(input[0], "exit") == 0)
		return (ft_exit_builtin(input), 0);
	else
		return (-1); //command not found in builtin
	return (0);
}


	// printf("--------------------TESTING EXPORT--------------------\n");
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);
	// printf("--------------------TESTING ENV--------------------\n");
	// input[0] = "env";
	// input[1] = NULL;
	// ft_env_builtin(input, &shell);

	// printf("--------------------ADDING TEST_VAR --------------------\n");
	// input[0] = "export";
	// input[1] = "TEST_VAR=\"test_value\"";
	// input[2] = NULL;
	// ft_export_builtin(input, &shell);
	// printf("--------------------SHOULD BE TEST_VAR--------------------\n");
	// input[0] = "env";
	// input[1] = NULL;
	// ft_env_builtin(input, &shell);
	// printf("--------------------UNSETTING TEST_VAR--------------------\n");
	// input[0] = "unset";
	// input[1] = "TEST_VAR";
	// input[2] = NULL;
	// ft_unset_builtin(input, &shell);
	// printf("--------------------SHOULD NOT BE TEST_VAR--------------------\n");
	// input[0] = "env";
	// input[1] = NULL;
	// ft_env_builtin(input, &shell);


	/////////////////////////////////////////

	// printf("\n\ncd ./test : RESULT\n");
	// input[0] = "cd";
	// input[1] = "./test";
	// input[2] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);

	// printf("\n\ncd ./test2 : RESULT\n");
	// input[0] = "cd";
	// input[1] = "./test2";
	// input[2] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);

	// printf("\n\ncd ../test3 :RESULT\n");
	// input[0] = "cd";
	// input[1] = "../test3";
	// input[2] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);

	// printf("\n\ncd - : RESULT\n");
	// input[0] = "cd";
	// input[1] = "-";
	// input[2] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);

	// printf("\n\ncd - : RESULT\n");
	// input[0] = "cd";
	// input[1] = "-";
	// input[2] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);

	// printf("cd :\n\nRESULT\n");
	// input[0] = "cd";
	// input[1] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);

	// printf("\n\ncd ./Desktop : RESULT\n");
	// input[0] = "cd";
	// input[1] = "./Desktop";
	// input[2] = NULL;
	// ft_cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// ft_export_builtin(input, &shell);
