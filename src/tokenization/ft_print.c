/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:38:08 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/16 09:42:09 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_token_list(t_token *token)
{
	t_token	*head;

	head = token;
	while (token)
	{
		printf("Prev: %p\t", token->prev);
		printf("Curr: %p\t", token);
		printf("Next: %p\t", token->next);
		printf("\tstr= %s", token->word);
		printf(" [%d]\n", token->type);
		token = token->next;
	}
	token = head;
}

void	ft_print_exec_list(t_exec *exec)
{
	t_exec	*head;
	int		i;

	head = exec;
	while (exec)
	{
		printf("current address:\t%p\n", exec);
		if (exec->word)
		{
			i = 0;
			while (exec->word[i])
			{
				printf("Word[%d]:\t%s\n", i, exec->word[i]);
				i++;
			}
		}
		printf("infile:\t\t%s [%d]\n", exec->infile, exec->flag);
		printf("outfile:\t%s [%d]\n", exec->outfile, exec->fd_outfile);
		printf("heredoc:\t%s\n", exec->heredoc);
		printf("pipe address:\t%p\n\n", exec->pipe);
		exec = exec->pipe;
	}
	exec = head;
}

int	ft_ms_count_words(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i])
		i++;
	return (i);
}
