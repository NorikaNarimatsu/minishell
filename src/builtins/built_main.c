/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:49:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 14:01:16 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_buildin(t_shell *shell)
{
	char	**input;

	input = shell->execution->word;
	if (strcmp(input[0], "echo") == 0)
		echo_builtin(input, shell);
	else if (strcmp(input[0], "env") == 0)
		env_builtin(input, shell);
	else if (strcmp(input[0], "export") == 0)
		export_builtin(input, shell);
	else if (strcmp(input[0], "unset") == 0)
		unset_builtin(input, shell);
	else if (strcmp(input[0], "pwd") == 0)
		pwd_builtin(input, shell);
	else if (strcmp(input[0], "cd") == 0)
		cd_builtin(input, shell);
	else if (strcmp(input[0], "exit") == 0)
		exit_builtin(input, shell);
	else
		printf("No command found\n");
	return (0);
}


	// printf("--------------------TESTING EXPORT--------------------\n");
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);
	// printf("--------------------TESTING ENV--------------------\n");
	// input[0] = "env";
	// input[1] = NULL;
	// env_builtin(input, &shell);

	// printf("--------------------ADDING TEST_VAR --------------------\n");
	// input[0] = "export";
	// input[1] = "TEST_VAR=\"test_value\"";
	// input[2] = NULL;
	// export_builtin(input, &shell);
	// printf("--------------------SHOULD BE TEST_VAR--------------------\n");
	// input[0] = "env";
	// input[1] = NULL;
	// env_builtin(input, &shell);
	// printf("--------------------UNSETTING TEST_VAR--------------------\n");
	// input[0] = "unset";
	// input[1] = "TEST_VAR";
	// input[2] = NULL;
	// unset_builtin(input, &shell);
	// printf("--------------------SHOULD NOT BE TEST_VAR--------------------\n");
	// input[0] = "env";
	// input[1] = NULL;
	// env_builtin(input, &shell);


	/////////////////////////////////////////

	// printf("\n\ncd ./test : RESULT\n");
	// input[0] = "cd";
	// input[1] = "./test";
	// input[2] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);

	// printf("\n\ncd ./test2 : RESULT\n");
	// input[0] = "cd";
	// input[1] = "./test2";
	// input[2] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);

	// printf("\n\ncd ../test3 :RESULT\n");
	// input[0] = "cd";
	// input[1] = "../test3";
	// input[2] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);

	// printf("\n\ncd - : RESULT\n");
	// input[0] = "cd";
	// input[1] = "-";
	// input[2] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);

	// printf("\n\ncd - : RESULT\n");
	// input[0] = "cd";
	// input[1] = "-";
	// input[2] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);

	// printf("cd :\n\nRESULT\n");
	// input[0] = "cd";
	// input[1] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);

	// printf("\n\ncd ./Desktop : RESULT\n");
	// input[0] = "cd";
	// input[1] = "./Desktop";
	// input[2] = NULL;
	// cd_builtin(input, &shell);
	// input[0] = "export";
	// input[1] = NULL;
	// export_builtin(input, &shell);
