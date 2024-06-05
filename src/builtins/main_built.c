/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:49:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/05 21:30:03 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	data;


	(void) argc;
	data.env = envp;

	if (ft_strcmp(argv[1], "echo") == 0)
		echo_builtin(argv);
	// else if (ft_strcmp(argv[1], "cd") == 0)
	// 	cd_builtin(argv);
	else if (ft_strcmp(argv[1], "pwd") == 0)
		pwd_builtin(argv, &data);
	// else if (ft_strcmp(argv[1], "export") == 0)
	// 	export_builtin(argv);
	else if (ft_strcmp(argv[1], "unset") == 0)
		unset_builtin(argv, &data);
	else if (ft_strcmp(argv[1], "env") == 0)
		env_builtin(argv, &data);
	// else if (ft_strcmp(argv[1], "exit") == 0)
	// 	exit_builtin(argv);
	else
		printf("Not build in command\n");
	while(data.env != NULL)
	{
		printf("%s\n", *data.env);
		data.env++;
	}
	return (0);
}
