/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_built.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 15:21:39 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/05 15:42:57 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env_builtin(char **argv, t_data *data)
{
	int	i;

	if (argv && argv[2])
		return (-1);
	i = 0;
	if (!data->env)
		return (EXIT_FAILURE);
	while (data->env[i])
		ft_putendl_fd(data->env[i++], 1);
	return (EXIT_SUCCESS);
}
