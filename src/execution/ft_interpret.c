/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_interpret.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:42:57 by nnarimat          #+#    #+#             */
/*   Updated: 2024/08/07 19:03:16 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_interpret(t_shell *shell)
{
	int	status;

	shell->n_cmd = ft_count_command(shell->execution);
	if (ft_ms_count_words(shell->execution->word) == 0 && shell->n_cmd == 1)
		return (shell->exit_status);
	shell->saved_stdin = dup(STDIN_FILENO);
	if (shell->saved_stdin == -1)
		return (perror("dup stdin"), DUPERR);
	shell->saved_stdout = dup(STDOUT_FILENO);
	if (shell->saved_stdout == -1)
		return (perror("dup stdout"), DUPERR);
	if (shell->n_cmd == 1)
		status = ft_execute_single(shell);
	else
		status = ft_execute_pipe(shell, shell->execution);
	if (ft_restore_io(shell->saved_stdin, shell->saved_stdout) == DUPERR)
		return (DUPERR);
	// sleep(2);
	// printf("PARENT FDS BEFORE\n");
	// ft_print_open_fds();
	shell->exit_status = status;
	close(shell->saved_stdin);
	close(shell->saved_stdout);
	// printf("PARENT FDS AFTER\n");
	// ft_print_open_fds();
	return (status);
}

/* if it sis a sigle command and
dub std in and stdout
check whether builtin
yes -> restore to original fds

*/
