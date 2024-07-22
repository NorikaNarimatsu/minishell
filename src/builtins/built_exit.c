/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:38:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/20 18:02:24 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h" // TODO? UPDATE SHLVL when you exit

int	ft_exit_builtin(char **input, t_shell *shell)
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
				ft_putstr_fd("exit: numeric argument required\n", 2);
				return (shell->exit_status = 255, 255);
			}
			i++;
		}
		exit_status = ft_atoi(input[1]);
	}
	else
		exit_status = shell->exit_status;
	shell->exit_status = exit_status;
	return (exit(exit_status), exit_status);
}
