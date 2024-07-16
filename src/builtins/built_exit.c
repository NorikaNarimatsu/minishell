/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:38:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/16 09:25:21 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_builtin(char **input)
{
	int		exit_status;
	int		i;
	char	*p;

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

// nnarimat@f1r6s17:~$ exit hello 89
// exit
// bash: exit: hello: numeric argument required
// f1r6s17% echo $?
// 2
// f1r6s17% bash
// nnarimat@f1r6s17:~$ exit 89 hello
// exit
// bash: exit: too many arguments
// nnarimat@f1r6s17:~$ echo $?
// 1
// nnarimat@f1r6s17:~$ exit 89 93
// exit
// bash: exit: too many arguments
// nnarimat@f1r6s17:~$ echo $?
// 1
// nnarimat@f1r6s17:~$ exit 89
// exit
// f1r6s17% echo $?
// 89
