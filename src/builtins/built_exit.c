/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:38:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 14:37:45 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exit_builtin(char **input, t_shell *shell)
{
	int		exit_status;
	int		i;
	char	*p;

	(void)shell;
	exit_status = 0;
	i = 0;
	p = input[1];
	printf("exit\n");
	if (input[1])
	{
		while (p[i] != '\0')
		{
			if (!isdigit(p[i]))
			{
				fprintf(stderr, "exit: numeric argument required\n");
				exit(255);
			}
			i++;
		}
		exit_status = atoi(input[1]);
	}
	exit(exit_status); // UPDATE EXIT STATUS OF STRUCT FOR EXPANDER
}
// TODO? UPDATE SHLVL when you exit
