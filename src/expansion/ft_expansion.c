/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_expansion.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/17 16:48:22 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	return (0);
}

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
		return (exp->len = 0, 0);
	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
		len++;
	if (len == 1 && (line[len] == '$' || line[len] == '?'))
	{
		exp->key = ft_substr(line, 1, len);
		if (!exp->key)
			return (MALERR);
		exp->len = 2;
	}
	else
	{
		exp->key = ft_substr(line, 1, len - 1);
		if (!exp->key)
			return (MALERR);
		exp->len = len;
	}
	return (0);
}

int	ft_expansion(char *line, t_env *env, t_expan *exp)
{
	int		pos;

	pos = ft_exp_needed(line, exp);
	if (pos != 0)
		return (0);
	while (line[pos])
	{
		if (ft_get_temp(&line[pos], exp) < 0)
			return (MALERR);
		pos += exp->len;
		if (ft_get_key(&line[pos], exp) < 0)
			return (MALERR);
		pos += exp->len;
		if (exp->key != NULL && ft_get_env(env, exp) < 0)
			return (MALERR);
		exp->temp = ft_expstring(&exp->temp, &exp->key);
		if (!exp->temp)
			return (MALERR);
		exp->exp_line = ft_expstring(&exp->exp_line, &exp->temp);
		if (!exp->exp_line)
			return (MALERR);
	}
	ft_free_small_expansion(exp);
	return (0);
}
