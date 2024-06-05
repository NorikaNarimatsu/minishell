/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:49:52 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/05 18:37:42 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	pwd_builtin(char **argv, t_data *data)
{
	char	buf[PATH_MAX];

	(void) argv;
	data->cwd = getcwd(buf, PATH_MAX);
	if (data->cwd)
	{
		ft_putendl_fd(data->cwd, STDOUT_FILENO);
		return (EXIT_SUCCESS);
	}
	printf("cwd not found?");
	return (EXIT_FAILURE);
}
