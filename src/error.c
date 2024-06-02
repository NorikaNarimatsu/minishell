/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:31:13 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/02 16:31:21 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fatal_error(char *message)
{
	dprintf(STDERR_FILENO, "Fatal Error: %s\n", message);
	exit(1);
}

void	error_exit(char *location, char *message, int status)
{
	dprintf(STDERR_FILENO, "minishell: %s: %s\n", location, message); //to do
	exit(status);
}