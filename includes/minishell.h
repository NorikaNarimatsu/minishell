/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:09:53 by nnarimat          #+#    #+#             */
/*   Updated: 2024/06/05 22:12:44 by nnarimat         ###   ########.fr       */
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

typedef struct s_data
{
	char		**env;
	char		*cwd;
	char		*owd;
}	t_data;

// typedef struct s_env
// {
// 	char		*env;
// 	char		*key;
// 	char		*value;
// 	struct s_env	*next;
// }



// error.c
void	fatal_error(char *message);
void	error_exit(char *location, char *message, int status);


// path.c
void	validate_access(char *path, char *filename);
char	*search_path(char *filename);

//builtins
int	echo_builtin(char **args);
int	env_builtin(char **argv, t_data *data);
int	pwd_builtin(char **args, t_data *data);
int	unset_builtin(char **args, t_data *data);

#endif