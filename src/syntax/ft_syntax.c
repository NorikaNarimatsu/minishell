/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_syntax.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/15 10:51:42 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/15 17:04:21 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
Error cases:
<|
> |
>>|
<<|
<< <
| |
||

>>>
>>>>
<<<<

Unfinished quotes!

echo |> norika >
=
syntax error near unexpected token `newline'

| echo norika
=
syntax error near unexpected token `|'

< infile > outfile |
=
syntax error near unexpected token `|'



-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
mdraper@f1r7s4:~$ echo test | >
bash: syntax error near unexpected token `newline'

*/

void	ft_syn_dquote(t_syn *syntax)
{
	if (syntax->squote == 1)
		return ;
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
				-1);
	else if (syntax->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), \
				-1);
	return (0);
}

int	ft_syn_output(t_syn *syntax)
{
	syntax->output++;
	if (syntax->output == 3)
		return (ft_putstr_fd("syntax error near unexpected token `>'\n", 2), \
				-1);
	else if (syntax->input >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `<'\n", 2), \
				-1);
	return (0);
}

int	ft_syn_pipe(t_syn *syntax)
{
	syntax->pipe++;
	if (syntax->pipe == 2)
		return (-1);
	else if (syntax->input >= 1 || syntax->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				-1);
	return (0);
}

int	ft_find_character(char c, t_syn *syntax)
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

void	ft_reset_struct(t_syn *syntax)
{
	ft_bzero(syntax, sizeof(t_syn));
}

int	ft_first_check(char *line)
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
				-1);
		if (!ft_isspace(line[i]) && line[i] != '|')
			flag = 1;
		i++;
	}
	return (0);
}

int	ft_final_check(t_syn *syntax)
{
	if (syntax->dquote == 1 || syntax->squote == 1)
		return (ft_putstr_fd("Syntax error (unclosed quotes)\n", 2), -1);
	else if (syntax->pipe == 1)
		return (ft_putstr_fd("syntax error near unexpected token `|'\n", 2), \
				-1);
	else if (syntax->input >= 1 || syntax->output >= 1)
		return (ft_putstr_fd("syntax error near unexpected token `newline'\n", \
				2), -1);
	return (0);
}

int	ft_syntax(char *line)
{
	t_syn	*syntax;
	int		i;

	i = 0;
	syntax = ft_calloc(1, sizeof(t_syn));
	if (!syntax)
		return (MALERR);
	if (ft_first_check(line) == -1)
		return (-1);
	while (line[i])
	{
		if (ft_isinvalid(line[i]))
		{
			if (ft_find_character(line[i], syntax) == -1)
				return (ft_putstr_fd("Syntax error\n", 2), -1);
		}
		else if (!ft_isspace(line[i]) && syntax->dquote == 0 \
				&& syntax->squote == 0)
			ft_reset_struct(syntax);
		i++;
	}
	if (ft_final_check(syntax) == -1)
		return (-1);
	return (0);
}
