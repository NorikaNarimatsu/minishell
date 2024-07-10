/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/09 13:09:53 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/10 13:22:08 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/inc/libft.h"
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
# include <error.h>

# define PATH_MAX	4096

typedef struct s_env
{
	char			*env;
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

enum e_token
{
	T_WORD,
	T_INPUT,
	T_OUTPUT,
	T_HEREDOC,
	T_APPEND,
	T_PIPE,
	T_ENV,
	T_EOF
};

typedef struct s_token
{
	char			*word;
	enum e_token	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_exec
{
	char			**word;		// command/arguments
	int				fd_infile;
	int				fd_outfile;
	char			*infile;	// Append and infile | Already open it! (and close if already one opened). Append have different flags then for Append. Ask Norika for this.
	char			*outfile;
	char			*heredoc;
	struct s_exec	*pipe;		// linked list to this struct
}	t_exec;

typedef struct s_expan
{
	char			*temp;
	char			*key;
	char			*exp_line;
	int				single_double_quote;
	int				need_to_expand;
	int				len;
	int				exit_status;
}	t_expan;

typedef struct s_shell
{
	char	*cwd;
	char	*owd;
	t_env	*env;
	t_expan	*expanding;
	int		token_flag;
	t_token	*ll_token;
	t_exec	*execution;
}	t_shell;

enum e_errno
{
	MALERR = -1,		// malloc error
	SYNERR = -2,		// syntax error
	CNFERR = -3,		// command not found
};

/*		Norika						*/

// error.c
void	fatal_error(char *message);
void	error_exit(char *location, char *message, int status);


// path.c
void	validate_access(char *path, char *filename);
char	*search_path(char *filename);

//builtins
int		echo_builtin(char **args, t_shell *shell);
int		env_builtin(char **argv, t_shell *shell);
int		pwd_builtin(char **args, t_shell *shell);

t_env	*init_env(char **env);
void	print_env(t_env *env);



/*		Martijn						*/

/*		ft_error					*/
void	ft_free_string(char **str);
void	ft_free_t_token(t_token	**ll_token);

/*		ft_is						*/
int		ft_isword(char c);
int		ft_isoneredirection(char c);
int		ft_istworedirection(char *str);
int		ft_ispipe(char c);
int		ft_issquote(char c);
int		ft_isdquote(char c);

/*		ft_len						*/
int		ft_lenword(char *str);
int		ft_lenredirection(char *str);
int		ft_lenpipe(char *str);
int		ft_lensquote(char *str);
int		ft_lendquote(char *str);

/*		ft_make_and_fill_list		*/
t_token	*ft_create_token(void);
t_exec	*ft_create_exec(void);
int		ft_create_token_list(t_token *token);
int		ft_create_new_and_fill_type(t_token *token, enum e_token type);
int		ft_fill_word(char *str, t_token *token, int (*strlen_func)(char *));

/*		ft_token					*/
int		ft_word(char *str, t_token *token);
int		ft_redirection(char *str, t_token *token);
int		ft_pipe(char *str, t_token *token);
int		ft_single_quote(char *str, t_token *token, int flag);
int		ft_double_quote(char *str, t_token *token, int flag);

/*		ft_print					*/
void	ft_print_token_list(t_token *token);
void	ft_print_exec_list(t_exec *exec);

/*		ft_print					*/
void	get_errdescr(enum e_errno error);
void	ft_free_t_token(t_token	**ll_token);
int		ft_ms_count_words(char **str);

/*		ft_execution				*/
int		ft_transfer_for_exec(t_token *token, t_exec *exec);

/*		ft_tokenization				*/
void	ft_tokenization(char *str, t_shell *shell);

/*		ft_expansion				*/
int		ft_expansion(char *line, t_env *env, t_expan *expanding);
t_expan *ft_create_expansion(void);


#endif