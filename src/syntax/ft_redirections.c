/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_redirections.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/16 09:13:04 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/24 15:51:27 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_syn_dquote(t_syn *syntax)
{
	if (syntax->squote == 1)
		return ;
	if (syntax->dquote == 1)
		ft_bzero(syntax, sizeof(t_syn));
	else
	{
		ft_bzero(syntax, sizeof(t_syn));
		syntax->dquote = 1;
	}
	return ;
}

void	ft_syn_squote(t_syn *syntax)
{
	if (syntax->dquote == 1)
		return ;
	if (syntax->squote == 1)
		ft_bzero(syntax, sizeof(t_syn));
	else
	{
		ft_bzero(syntax, sizeof(t_syn));
		syntax->squote = 1;
	}
	return ;
}

int	ft_syn_input(t_syn *syntax)
{
	syntax->input++;
	if (syntax->input == 3 || (syntax->output == 2 && syntax->flag == 1))
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
	if (syntax->output == 3 || (syntax->output == 2 && syntax->flag == 1))
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
