/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_syntax.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 10:51:42 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/16 09:30:43 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_character(char c, t_syn *syntax)
{
	int	error;

	error = 0;
	if (c == '"')
		ft_syn_dquote(syntax);
	else if (c == '\'')
		ft_syn_squote(syntax);
	if (syntax->dquote == 1 || syntax->squote == 1)
		return (error);
	else if (c == '<')
		error = ft_syn_input(syntax);
	else if (c == '>')
		error = ft_syn_output(syntax);
	else if (c == '|')
		error = ft_syn_pipe(syntax);
	return (error);
}

static int	ft_first_check(char *line)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (line[i])
	{
		if (line[i] == '|' && flag == 0)
			return (\
				ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				SYNERR);
		if (!ft_isspace(line[i]) && line[i] != '|')
			flag = 1;
		i++;
	}
	return (0);
}

static int	ft_final_check(t_syn *syntax)
{
	if (syntax->dquote == 1 || syntax->squote == 1)
		return (ft_putstr_fd("Syntax error (unclosed quotes)\n", 2), SYNERR);
	else if (syntax->pipe == 1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				SYNERR);
	else if (syntax->input >= 1 || syntax->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `newline'\n", \
				2), SYNERR);
	return (0);
}

void	ft_free_syntax(t_syn **syntax)
{
	if (!syntax || !*syntax)
		return ;
	free(*syntax);
	*syntax = NULL;
}

int	ft_syntax(char *line)
{
	t_syn	*syntax;
	int		i;

	i = 0;
	syntax = ft_calloc(1, sizeof(t_syn));
	if (!syntax)
		return (MALERR);
	if (ft_first_check(line) == SYNERR)
		return (-1);
	while (line[i])
	{
		if (ft_isinvalid(line[i]))
		{
			if (ft_find_character(line[i], syntax) == SYNERR)
				return (SYNERR);
		}
		else if (!ft_isspace(line[i]) && syntax->dquote == 0 \
				&& syntax->squote == 0)
			ft_bzero(syntax, sizeof(t_syn));
		i++;
	}
	if (ft_final_check(syntax) == SYNERR)
		return (SYNERR);
	return (0);
}
