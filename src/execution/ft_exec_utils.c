/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 16:29:44 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/08 11:16:31 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_command(t_exec *exec)
{
	int	count;

	count = 0;
	while (exec)
	{
		count++;
		exec = exec->pipe;
	}
	return (count);
}

void	ft_error_exit(char *message, int exit_code)
{
	ft_putstr_fd(message, STDERR_FILENO);
	exit(exit_code);
}

void	ft_close_fd(int *fd)
{
	if (fd && *fd >= 0)
	{
		close(*fd);
		*fd = -1;
	}
}
