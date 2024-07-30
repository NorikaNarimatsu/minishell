/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_init_and_error.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/30 15:41:12 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/30 20:57:05 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_reset(t_shell *shell)
{
	ft_free_string(&shell->line);
	if (shell->execution)
	{
		if (shell->execution->pipe)
			ft_free_s_exec(&shell->execution->pipe);
		ft_free_array(&shell->execution->word);
		ft_free_string(&shell->execution->infile);
		ft_free_string(&shell->execution->outfile);
		ft_free_array(&shell->execution->heredoc);
		shell->execution->fd_infile = 8;
		shell->execution->is_end_append = 1;
		ft_bzero(shell->execution, sizeof(t_exec));
	}
	shell->token_flag = 1;
	shell->n_cmd = 0;
	shell->saved_stdin = 0;
	shell->saved_stdout = 0;
	ft_ms_signal(shell, INTERACTIVE);
}

void	ft_free_minishell(t_shell **shell)
{
	if (!shell || !*shell)
		return ;
	if ((*shell)->line)
		ft_free_string(&(*shell)->line);
	if ((*shell)->env)
		ft_free_env_list(&(*shell)->env);
	if ((*shell)->execution)
		ft_free_s_exec(&(*shell)->execution);
	free(*shell);
	*shell = NULL;
}

t_shell	*ft_init_shell(char **env)
{
	t_shell	*shell;

	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = ft_init_env(env);
	if (!shell->env)
		return (ft_free_minishell(&shell), NULL);
	shell->execution = ft_calloc(1, sizeof(t_exec));
	if (!shell->execution)
		return (ft_free_minishell(&shell), NULL);
	ft_ms_signal(shell, INTERACTIVE);
	return (shell);
}

static void	ft_print_err_msg(int index)
{
	int			max_index;
	const char	*err_msg[] = {"exit\n",
		"Malloc error\n",
		"Pipe error\n",
		"Dup error\n",
		"Chdir (path) error\n",
		"Getcwd error\n",
		"Fork error\n"
	};

	max_index = sizeof(err_msg) / sizeof(err_msg[0]);
	if (index >= 1 && index < max_index)
		ft_putstr_fd((char *)err_msg[index], 2);
	else if (index == 0)
		ft_putstr_fd((char *)err_msg[index], 1);
}

int	ft_ms_exit(t_shell **shell, int error_code)
{
	int	exit_code;

	if (error_code >= -1)
		ft_print_err_msg(-error_code);
	exit_code = 0;
	if (*shell)
		exit_code = (*shell)->exit_status;
	if (error_code < 0)
		exit_code = EXIT_FAILURE;
	rl_clear_history();
	ft_free_minishell(shell);
	return (exit_code);
}
