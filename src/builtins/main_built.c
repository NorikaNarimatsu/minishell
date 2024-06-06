/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:49:00 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/06 15:08:39 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_env(t_env *env)
{
	while (env)
	{
		printf("env: %s\n", env->env);
		printf("key: %s\n", env->key);
		printf("value: %s\n\n", env->value);
		env = env->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void) argc;
	data.env_copy = init_env(envp);
	if (ft_strcmp(argv[1], "echo") == 0)
		echo_builtin(argv, &data);
	else if (ft_strcmp(argv[1], "unset") == 0)
		unset_builtin(argv, &data);
	else if (ft_strcmp(argv[1], "env") == 0)
		env_builtin(argv, &data);
	else if (ft_strcmp(argv[1], "pwd") == 0)
		pwd_builtin(argv, &data);

	// else if (ft_strcmp(argv[1], "cd") == 0)
	// 	cd_builtin(argv);
	// else if (ft_strcmp(argv[1], "export") == 0)
	// 	export_builtin(argv);
	// else if (ft_strcmp(argv[1], "exit") == 0)
	// 	exit_builtin(argv);
	else
		printf("Not build in command\n");

	return (0);
}



	// printf("-----------\n");
	// t_env	*current;
	// current = data.env_copy;
	// while (current)
	// {
	// 	ft_putendl_fd(current->env, 1);
	// 	current = current->next;
	// }
	// return (EXIT_SUCCESS);
	// printf("-----------\n");