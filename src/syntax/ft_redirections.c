/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redirections.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:13:04 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/19 20:09:12 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syn_dquote(t_syn *syntax)
{
	if (syntax->squote == 1)
		return ;
	syntax->output = 0;
	syntax->input = 0;
	syntax->pipe = 0;
	if (syntax->dquote == 1)
		syntax->dquote = 0;
	else
		syntax->dquote = 1;
	return ;
}

void	ft_syn_squote(t_syn *syntax)
{
	if (syntax->dquote == 1)
		return ;
	syntax->output = 0;
	syntax->input = 0;
	syntax->pipe = 0;
	if (syntax->squote == 1)
		syntax->squote = 0;
	else
		syntax->squote = 1;
	return ;
}

int	ft_syn_input(t_syn *syntax)
{
	syntax->input++;
	if (syntax->input == 3)
		return (ft_putstr_fd("syntax error near unexpected token `<'\n", 2), \
				SYNERR);
	else if (syntax->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), \
				SYNERR);
	return (0);
}

int	ft_syn_output(t_syn *syntax)
{
	syntax->output++;
	if (syntax->output == 3)
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), \
				SYNERR);
	else if (syntax->input >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `<'\n", 2), \
				SYNERR);
	return (0);
}

int	ft_syn_pipe(t_syn *syntax)
{
	syntax->pipe++;
	if (syntax->pipe == 2)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				SYNERR);
	else if (syntax->input >= 1 || syntax->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				SYNERR);
	return (0);
}
