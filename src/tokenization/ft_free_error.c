/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_error.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/06 14:08:28 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/17 15:55:26 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_string(char **str)
{
	if (!str | !*str)
		return ;
	free(*str);
	*str = NULL;
}

void	ft_free_array(char ***str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	if (str[0])
	{
		while (str[0][i])
		{
			free(str[0][i]);
			str[0][i] = NULL;
			i++;
		}
		free(str[0]);
		str[0] = NULL;
	}
}

void	ft_free_t_token(t_token	**ll_token)
{
	t_token	*current;
	t_token	*next;

	if (!ll_token | !*ll_token)
		return ;
	current = *ll_token;
	while (current)
	{
		next = current->next;
		ft_free_string(&(current->word));
		free(current);
		current = NULL;
		current = next;
	}
	*ll_token = NULL;
}

void	ft_free_s_exec(t_exec **exec)
{
	t_exec	*next;

	if (!exec)
		return ;
	while (*exec)
	{
		next = (*exec)->pipe;
		ft_free_array(&(*exec)->word);
		ft_free_string(&(*exec)->infile);
		ft_free_string(&(*exec)->outfile);
		ft_free_array(&(*exec)->heredoc);
		free(*exec);
		*exec = NULL;
		*exec = next;
	}
}
