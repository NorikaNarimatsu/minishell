// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   expansion2.c                                       :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2024/06/19 11:41:43 by mdraper       #+#    #+#                 */
// /*   Updated: 2024/07/08 15:02:44 by mdraper       ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "minishell.h"

// int	ft_get_env(t_env *env, t_expan *exp)
// {
// 	int	value;

// 	exp->key_malloc = 1;
// 	value = ft_get_env_edgecases(exp);
// 	if (value < 0 || value == 1)
// 		return (value);
// 	while (env && exp->need_to_expand == 1)
// 	{
// 		if (ft_strcmp(env->key, exp->key) == 0)
// 		{
// 			ft_free_string(&exp->key);
// 			exp->key = ft_strdup(env->value);
// 			if (!exp->key)
// 				return (MALERR);
// 			return (1);
// 		}
// 		env = env->next;
// 	}
// 	ft_free_string(&exp->key);
// 	exp->key_malloc = 0;
// 	return (0);
// }

// int	ft_get_key(char *line, t_expan *exp)
// {
// 	int		len;

// 	len = 1;
// 	while (line[len] && (ft_isalnum(line[len]) || line[len] == '_'))
// 		len++;
// 	if (len == 1 && (line[len] == '$' || line[len] == '?'))
// 	{
// 		exp->key = ft_substr(line, 1, len);
// 		if (!exp->key)
// 			return (MALERR);
// 		exp->len = 2;
// 		return (0);
// 	}
// 	else
// 	{
// 		exp->key = ft_substr(line, 1, len - 1);
// 		if (!exp->key && len > 1)
// 		{
// 			exp->malloc_error = 1;
// 			return (MALERR);
// 		}
// 		exp->len = len;
// 	}
// 	return (0);
// }

// t_expan	*ft_create_expansion(void)
// {
// 	t_expan	*expansion;

// 	expansion = ft_calloc(1, sizeof(t_expan));
// 	if (!expansion)
// 		return (NULL);
// 	ft_bzero(expansion, sizeof(t_expan));
// 	return (expansion);
// }

// int	ft_expansion(char *line, t_env *env, t_expan *exp)
// {
// 	int		pos;

// 	if (ft_get_position(line) == (int)ft_strlen(line))
// 	{
// 		exp->exp_line = ft_strdup(line);
// 		if (!exp->exp_line)
// 			return (MALERR);
// 		return (0);
// 	}
// 	pos = 0;
// 	exp->strmal = 0;
// 	while (line[pos])
// 	{
// 		if (ft_get_temp(&line[pos], exp) < 0)
// 			return (MALERR);
// 		pos += exp->len;
// 		if (ft_get_key(&line[pos], exp) < 0)
// 			return (MALERR);
// 		pos += exp->len;
// 		if (ft_get_env(env, exp) < 0) // if 0, means not found. By return 1, it means it found something
// 			return (MALERR);
// 		exp->temp = ft_expstring(exp->temp, 1, exp->key, exp->key_malloc);
// 		if (!exp->temp)
// 			return (MALERR);
// 		exp->exp_line = ft_expstring(exp->exp_line, exp->strmal, exp->temp, 1);
// 		if (!exp->exp_line)
// 			return (MALERR);
// 		exp->strmal = 1;
// 	}
// 	printf("\n\nexp->exp_line = %s\n\n", exp->exp_line);
// 	return (0);
// }

// /*
// Think about memory free!
// */
