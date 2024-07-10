/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_is.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:01:36 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/08 13:55:11 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isseperator(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '$');
}

int	ft_isinvalid(char c)
{
	return (c == '<' || c == '>' || c == '|' || c == '\'' || c == '"');
}

int	ft_isword(char c)
{
	return (ft_isgraph(c) && !ft_isinvalid(c));
}

int	ft_isoneredirection(char c)
{
	return (c == '<' || c == '>');
}

int	ft_istworedirection(char *str)
{
	int	i;

	i = 0;
	if (!str || str[i] == '\0' || str[i + 1] == '\0')
		return (i);
	if ((str[i] == str[i + 1]) && (ft_isoneredirection(str[i]) == 1))
		return (2);
	return (0);
}

int	ft_ispipe(char c)
{
	return (c == '|');
}

int	ft_issquote(char c)
{
	return (c == '\'');
}

int	ft_isdquote(char c)
{
	return (c == '"');
}
