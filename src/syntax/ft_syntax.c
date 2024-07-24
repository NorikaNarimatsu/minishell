/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_syn.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 10:51:42 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/23 11:46:56 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_find_character(char c, t_syn *syn)
{
	int	error;

	error = 0;
	if (c == '"')
		ft_syn_dquote(syn);
	else if (c == '\'')
		ft_syn_squote(syn);
	if (syn->dquote == 1 || syn->squote == 1)
		return (error);
	else if (c == '<')
		error = ft_syn_input(syn);
	else if (c == '>')
		error = ft_syn_output(syn);
	else if (c == '|')
		error = ft_syn_pipe(syn);
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

static int	ft_final_check(t_syn *syn)
{
	if (syn->dquote == 1 || syn->squote == 1)
		return (ft_putstr_fd("syntax error (unclosed quotes)\n", 2), SYNERR);
	else if (syn->pipe == 1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				SYNERR);
	else if (syn->input >= 1 || syn->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `newline'\n", \
				2), SYNERR);
	return (0);
}

void	ft_free_syn(t_syn **syn)
{
	if (!syn || !*syn)
		return ;
	free(*syn);
	*syn = NULL;
}

int	ft_syntax(char *line, t_shell *shell)
{
	t_syn	*syn;
	int		i;

	i = 0;
	syn = ft_calloc(1, sizeof(t_syn));
	if (!syn)
		return (ft_free_minishell(&shell), MALERR);
	if (ft_first_check(line) == SYNERR)
		return (ft_free_syn(&syn), SYNERR);
	while (line[i])
	{
		if (ft_isinvalid(line[i]))
		{
			if (ft_find_character(line[i], syn) == SYNERR)
				return (ft_free_syn(&syn), SYNERR);
		}
		else if (!ft_isspace(line[i]) && syn->dquote == 0 && syn->squote == 0)
			ft_bzero(syn, sizeof(t_syn));
		else if (ft_isspace(line[i]) && syn->dquote == 0 && syn->squote == 0)
			syn->flag = 1;
		i++;
	}
	if (ft_final_check(syn) == SYNERR)
		return (ft_free_syn(&syn), SYNERR);
	return (ft_free_syn(&syn), 0);
}
