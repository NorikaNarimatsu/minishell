/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 13:09:53 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/08 11:15:26 by nnarimat         ###   ########.fr       */
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
# include <stdbool.h>
# include <signal.h>

# define PATH_MAX	4096
# define FDMAX		1024

enum e_token
{
	T_EOF,
	T_WORD,
	T_INPUT,
	T_OUTPUT,
	T_HEREDOC,
	T_APPEND,
	T_PIPE
};

enum e_errno
{
	MALERR = -1,
	SYNERR = -2,
	PIPERR = -3,
	DUPERR = -4,
	CHDERR = -5,
	CWDERR = -6,
	FRKERR = -7,
	SIGERR = -8
};

enum e_mode
{
	INTERACTIVE,
	HEREDOC,
	EXECUTION,
	IGNORE
};

typedef struct s_syn
{
	int	squote;
	int	dquote;
	int	input;
	int	output;
	int	pipe;
	int	flag;
}	t_syn;

typedef struct s_token
{
	char			*word;
	enum e_token	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

typedef struct s_exec
{
	char			**word;
	int				flag;
	int				fd_infile;
	int				fd_outfile;
	int				fd_heredoc;
	char			*infile;
	char			*outfile;
	char			**heredoc;
	bool			is_end_append;
	bool			is_end_infile;
	struct s_exec	*pipe;
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

typedef struct s_env
{
	char			*env;
	char			*key;
	bool			flag;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_shell
{
	int					n_cmd;
	int					token_flag;
	int					exit_status;
	int					saved_stdin;
	int					saved_stdout;
	t_env				*env;
	char				*line;
	t_exec				*execution;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;
}	t_shell;

extern int	g_sig;

/*		Norika						*/
// void	ft_print_open_fds(void);

/*	HEREDOC-----------------------*/
/*		ft_heredoc				*/
int		ft_heredoc(t_shell *shell);
/*		ft_heredoc_expansion	*/
int		ft_expansion_heredoc(char **line, t_shell *shell);

/*	BUILTIN-----------------------*/
/*		builtins				*/
bool	is_builtin(char *command);
int		ft_unset_builtin(char **input, t_env **env);

/*		builtins-cd		*/
int		ft_cd_builtin(char **input, t_env **env);
int		ft_update_env_value(t_env *env_list, char *key, char *value);
char	*ft_find_env_value(t_env *env_list, char *key);

/*		builtins-echo	*/
int		ft_echo_builtin(char **input);

/*		builtins-env	*/
int		ft_env_builtin(char **input, t_env *env);

/*		builtins-exit	*/
int		ft_exit_builtin(char **input, t_shell *shell);
int		ft_check_valid_longlong(const char *str);

/*		builtins-export	*/
int		ft_export_builtin(char **input, t_env **env);
int		add_new_env_node(t_env **env_list, char *input);
int		ft_replace_env_value(t_env *env_list, char *input);
t_env	*find_min_unflagged(t_env *env_list);

/*		builtins-pwd	*/
int		ft_pwd_builtin(t_env *env);

/*		builtins-unset	*/
int		ft_unset_builtin(char **input, t_env **env);

/*		builtins-utils	*/
bool	is_valid_identifier(char *input);
bool	is_exist_identifier(t_env *env_list, char *key);
int		is_valid_directory(char *path);

/*	ENVP-----------------------*/
char	**ft_env_to_array(t_env *env_list);
void	ft_reset_env_flags(t_env *env_list);
t_env	*ft_create_env_node(char *env_str);
t_env	*ft_init_env(char **env);

/*	EXECUTION-----------------------*/
/*		interpretation				*/
int		ft_interpret(t_shell *shell);
int		ft_execute_builtin(t_exec *exec, t_env **env, t_shell *shell);
int		ft_execute_single(t_shell *shell);
int		ft_execute_pipe(t_shell *shell, t_exec *exec);
void	ft_execute_command(t_exec *exec, t_env *env, t_shell *shell);

/*		shlvl				*/
int		ft_replace_shlvl(t_env **env_list);

/*		redirect				*/
int		ft_open_io(t_exec *exec);
int		ft_redirect_io(t_exec *exec);
int		ft_restore_io(t_shell *shell);
void	ft_manage_redirect(t_shell *shell, t_exec *exec, int *fd, int i);

/*		path				*/
char	*ft_path_error(t_exec *exec, t_env *env, char *path);

/*		utils				*/
void	ft_error_exit(char *message, int exitcode);
int		ft_count_command(t_exec *exec);
void	ft_close_fd(int *fd);

/*		free				*/
void	ft_free_env_node(t_env **env);
void	ft_free_env_list(t_env **current);

/*		Martijn						*/

/*	EXPANSION-----------------------*/
/*		ft_create_error				*/
t_expan	*ft_create_expansion(t_shell *shell);
void	ft_free_small_expansion(t_expan *exp);
void	ft_free_expansion(t_expan **exp);

/*		ft_exp_utils				*/
int		ft_get_position(const char *line, t_expan *exp);
char	*ft_expstring(char **s1, char **s2, char **s3);
int		ft_strlen_dollar_sign(char *str);
int		ft_exp_needed(char *line, t_expan *exp);

/*		ft_expansion				*/
int		ft_get_env_edgecases(t_expan *exp);
int		ft_get_env(t_env *env, t_expan *exp);
int		ft_get_key(const char *line, t_expan *exp);
int		ft_get_temp(const char *line, t_expan *exp);
int		ft_expansion(t_shell *shell);

/*	SYNTAX ERROR--------------------*/
/*		ft_redirections				*/
void	ft_syn_dquote(t_syn *syntax);
void	ft_syn_squote(t_syn *syntax);
int		ft_syn_input(t_syn *syntax);
int		ft_syn_output(t_syn *syntax);
int		ft_syn_pipe(t_syn *syntax);

/*		ft_syntax					*/
int		ft_syntax(char *line, t_shell *shell);

/*	TOKENIZATION--------------------*/
/*		ft_execution				*/
int		ft_transfer_word(t_token *token, t_exec *exec);
int		ft_transfer_for_exec(t_token *token, t_exec *exec);

/*		ft_exetransfer				*/
int		ft_transfer_pipe(t_token *token, t_exec *exec);
int		ft_transfer_append(t_token **token, t_exec *exec);
int		ft_transfer_heredoc(t_token **token, t_exec *exec);
int		ft_transfer_input(t_token **token, t_exec *exec);
int		ft_transfer_output(t_token **token, t_exec *exec);

/*		ft_free_error				*/
void	ft_free_string(char **str);
void	ft_free_array(char ***str);
void	ft_free_t_token(t_token	**ll_token);
void	ft_free_s_exec(t_exec **exec);
void	ft_free_fd(int **fd);
void	ft_free_pid(pid_t **pid);

/*		ft_is						*/
int		ft_isinvalid(char c);
int		ft_isword(char c);
int		ft_isoneredirection(char c);
int		ft_istworedirection(char *str);

/*		ft_len						*/
int		ft_lenword(char *str);
int		ft_lenredirection(char *str);
int		ft_lenpipe(char *str);
int		ft_lensquote(char *str);
int		ft_lendquote(char *str);

/*		ft_make_and_fill_list		*/
t_token	*ft_create_token(void);
int		ft_create_token_list(t_token *token);
int		ft_create_new_and_fill_type(t_token *token, enum e_token type);
int		ft_fill_word(char *str, t_token *token, int (*strlen_func)(char *));

/*		ft_print					*/
void	ft_print_token_list(t_token *token);
void	ft_print_exec_list(t_exec *exec);
int		ft_ms_count_words(char **str);

/*		ft_token					*/
int		ft_word(char *str, t_token *token, int flag);
int		ft_redirection(char *str, t_token *token, int *flag);
int		ft_pipe(char *str, t_token *token, int *flag);
int		ft_single_quote(char *str, t_token *token, int flag);
int		ft_double_quote(char *str, t_token *token, int flag);

/*		ft_tokenization				*/
int		ft_tokenization(t_shell *shell);

/*	SIGNALS-------------------------*/
/*		ft_signals					*/
int		ft_ms_signal(t_shell *shell, int mode);
/*		ft_signal_exit				*/
void	ft_recieved_signal_exit_status(t_shell *shell);
void	ft_signal_exit_status(t_shell *shell, pid_t	*pid);

/*	MAIN----------------------------*/
/*		ft_init_and_error			*/
void	ft_reset(t_shell *shell);
void	ft_free_minishell(t_shell **shell);
t_shell	*ft_init_shell(char **env);
int		ft_ms_exit(t_shell **shell, int error_code);

#endif