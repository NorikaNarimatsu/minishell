/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shlvl.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/26 16:02:26 by mdraper       #+#    #+#                 */
/*   Updated: 2024/07/26 16:50:45 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_reset_shlvl(t_env **env_list)
{
	char	*shlvl_value;
	char	*shlvl_whole;
	int		status;

	shlvl_value = ft_itoa(1);
	if (!shlvl_value)
		return (MALERR);
	shlvl_whole = ft_strjoin("SHLVL=", shlvl_value);
	if (!shlvl_value)
		return (ft_free_string(&shlvl_value), MALERR);
	status = add_new_env_node(env_list, shlvl_whole);
	ft_free_string(&shlvl_value);
	return (ft_free_string(&shlvl_value), ft_free_string(&shlvl_whole), status);
}
	
int	ft_replace_shlvl(t_env **env_list)
{
	int		shlvl;
	char	*shlvl_str;
	int		status;
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strcmp(current->key, "SHLVL") == 0)
		{
			shlvl = ft_atoi(current->value);
			shlvl++;
			shlvl_str = ft_itoa(shlvl);
			if (!shlvl_str)
				return (MALERR);
			status = ft_update_env_value(*env_list, "SHLVL", shlvl_str);
			return (ft_free_string(&shlvl_str), status);
		}
		current = current->next;
	}
	status = ft_reset_shlvl(env_list);
	return (status);
}
