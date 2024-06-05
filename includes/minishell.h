/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/05/09 13:09:53 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/06/05 22:01:08 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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

enum e_token
{
    T_WORD,
    T_OPERATER,
    T_EOF
};

typedef struct s_token
{
	char			*word;
	enum e_token	type;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;



/*		Martijn						*/

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
int		ft_create_token_list(t_token *token);
int		ft_fill_type_and_next(t_token *token, enum e_token type);
int		ft_fill_word(char *str, t_token *token, int (*strlen_func)(char *));

/*		ft_token					*/
int		ft_word(char *str, t_token *token);
int		ft_redirection(char *str, t_token *token);
int		ft_pipe(char *str, t_token *token);
int		ft_single_quote(char *str, t_token *token, int flag);
int		ft_double_quote(char *str, t_token *token, int flag);

/*		ft_print					*/
void	ft_print_linked_list(t_token *token);

void	my_func(char *str);

#endif