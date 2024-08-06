/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_heredoc_expansion.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/08/05 22:25:04 by mdraper       #+#    #+#                 */
/*   Updated: 2024/08/07 00:05:58 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_expansion_heredoc(char **line, t_shell *shell)
{
	t_expan	*exp;
	int		pos;

	exp = ft_create_expansion(shell);
	if (!exp)
		return (MALERR);
	pos = ft_exp_needed(*line, exp);
	if (pos == 1)
		return (ft_free_expansion(&exp), pos);
	while (line[0][pos])
	{
		if (ft_get_temp(&line[0][pos], exp) == MALERR)
			return (ft_free_expansion(&exp), MALERR);
		pos += exp->len;
		if (exp->key != NULL && ft_get_env(shell->env, exp) == MALERR)
			return (ft_free_expansion(&exp), MALERR);
		exp->exp_line = ft_expstring(&exp->temp, &exp->key, &exp->exp_line);
		if (!exp->exp_line)
			return (ft_free_expansion(&exp), MALERR);
	}
	ft_free_string(line);
	*line = ft_strdup(exp->exp_line);
	if (!*line)
		return (ft_free_expansion(&exp), MALERR);
	return (ft_free_expansion(&exp), 0);
}
