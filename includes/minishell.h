/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:09:53 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/02 16:39:51 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define PATH_MAX	4096

# include "../libft/includes/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <limits.h>
# include <string.h>

// error.c
void	fatal_error(char *message);
void	error_exit(char *location, char *message, int status);


// path.c
void	validate_access(char *path, char *filename);
char	*search_path(char *filename);

#endif