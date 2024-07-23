/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_exp_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/23 09:58:53 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_position(const char *line, t_expan *exp)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"')
			exp->single_double_quote++;
		if (line[i] == '\'' && exp->single_double_quote % 2 == 0)
		{
			i++;
			while (line[i] && line[i] != '\'')
				i++;
		}
		else if (line[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

char	*ft_expstring(char **s1, char **s2, char **s3)
{
	char	*result;

	result = NULL;
	if (!s1 || !s2)
		return (NULL);
	if (ft_strlen(*s1) > 0 && ft_strlen(*s2) > 0)
		result = ft_strjoin(*s1, *s2);
	else if (ft_strlen(*s1) == 0 && ft_strlen(*s2) > 0)
		result = ft_strdup(*s2);
	else if (ft_strlen(*s2) == 0)
		result = ft_strdup(*s1);
	ft_free_string(s1);
	ft_free_string(s2);
	if (!result)
		return (NULL);
	if (!s3 || !*s3)
		return (result);
	result = ft_expstring(s3, &result, NULL);
	return (result);
}

int	ft_strlen_dollar_sign(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isspace(str[i]))
		i++;
	return (i);
}

int	ft_exp_needed(t_shell *shell, t_expan *exp)
{
	exp->single_double_quote = 0;
	if (ft_get_position(shell->line, exp) == (int)ft_strlen(shell->line))
		return (ft_free_expansion(&exp), 1);
	exp->single_double_quote = 0;
	return (0);
}

// int	ft_exp_needed(const char *line, t_expan *exp)
// {
// 	exp->single_double_quote = 0;
// 	if (ft_get_position(line, exp) == (int)ft_strlen(line))
// 	{
// 		exp->exp_line = ft_strdup(line);
// 		if (!exp->exp_line)
// 			return (MALERR);
// 		ft_free_expansion(&exp);
// 		return (1);
// 	}
// 	exp->single_double_quote = 0;
// 	return (0);
// }