/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expansion.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/24 15:32:10 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_get_env_edgecases(t_expan *exp)
{
	if (exp->need_to_expand == 1 && ft_strlen_dollar_sign(exp->key) == 0)
	{
		ft_free_string(&exp->key);
		exp->key = ft_strdup("$");
		if (!exp->key)
			return (MALERR);
		return (1);
	}
	else if (ft_strcmp(exp->key, "$") == 0)
	{
		ft_free_string(&exp->key);
		exp->key = ft_itoa(getpid());
		if (!exp->key)
			return (MALERR);
		return (1);
	}
	else if (ft_strcmp(exp->key, "?") == 0)
	{
		ft_free_string(&exp->key);
		exp->key = ft_itoa(exp->exit_status);
		if (!exp->key)
			return (MALERR);
		return (1);
	}
	return (0);
}

static int	ft_get_env(t_env *env, t_expan *exp)
{
	int	value;

	value = ft_get_env_edgecases(exp);
	if (value != 0)
		return (value);
	while (env && exp->need_to_expand == 1)
	{
		if (ft_strcmp(env->key, exp->key) == 0)
		{
			ft_free_string(&exp->key);
			exp->key = ft_strdup(env->value);
			if (!exp->key)
				return (MALERR);
			return (1);
		}
		env = env->next;
	}
	ft_free_string(&exp->key);
	return (0);
}

static int	ft_get_key(const char *line, t_expan *exp)
{
	int		len;

	len = 1;
	if (line[0] == '\0')
		return (exp->len += 0, 0);
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	if (len == 1 && (line[len] == '$' || line[len] == '?'))
	{
		exp->key = ft_substr(line, 1, len);
		if (!exp->key)
			return (MALERR);
		exp->len += 2;
	}
	else
	{
		exp->key = ft_substr(line, 1, len - 1);
		if (!exp->key)
			return (MALERR);
		exp->len += len;
	}
	return (0);
}

static int	ft_get_temp(const char *line, t_expan *exp)
{
	int		i;

	i = ft_get_position(line, exp);
	exp->temp = ft_substr(line, 0, i);
	if (!exp->temp)
		return (MALERR);
	if (i == (int)ft_strlen(line))
		exp->need_to_expand = 0;
	else
		exp->need_to_expand = 1;
	exp->len = i;
	if (ft_get_key(&line[exp->len], exp) == MALERR)
		return (MALERR);
	return (0);
}

int	ft_expansion(t_shell *shell)
{
	t_expan	*exp;
	int		pos;

	exp = ft_create_expansion(shell);
	if (!exp)
		return (MALERR);
	pos = ft_exp_needed(shell, exp);
	if (pos == 1)
		return (ft_free_expansion(&exp), pos);
	while (shell->line[pos])
	{
		if (ft_get_temp(&shell->line[pos], exp) == MALERR)
			return (ft_free_expansion(&exp), MALERR);
		pos += exp->len;
		if (exp->key != NULL && ft_get_env(shell->env, exp) == MALERR)
			return (ft_free_expansion(&exp), MALERR);
		exp->exp_line = ft_expstring(&exp->temp, &exp->key, &exp->exp_line);
		if (!exp->exp_line)
			return (ft_free_expansion(&exp), MALERR);
	}
	shell->line = ft_strdup(exp->exp_line);
	if (!shell->line)
		return (ft_free_expansion(&exp), MALERR);
	return (ft_free_expansion(&exp), 0);
}
