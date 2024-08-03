/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 11:38:52 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/08/03 22:23:51 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_valid_longlong(const char *str)
{
	int	len_str;
	int	i;

	i = 0;
	len_str = ft_strlen(str);
	if (ft_check_string(str) == -1 || ft_check_char_after_digit(str) == -1)
		return (-1);
	if (str[i] == '-' || str[i] == '+')
	{
		if (len_str > 20)
			return (-1);
		else if (len_str == 20 \
			&& ((str[i] == '-' && ft_strcmp(str, "-9223372036854775808") > 0) \
			|| (str[i] == '+' && ft_strcmp(str, "+9223372036854775807") > 0)))
			return (-1);
	}
	else
	{
		if (len_str > 19)
			return (-1);
		else if (len_str == 19 && ft_strcmp(str, "9223372036854775807") > 0)
			return (-1);
	}
	return (0);
}

static int	ft_convert_exitstatus(char *p)
{
	if (ft_check_valid_longlong(p) == -1)
		return (ft_putstr_fd("exit: numeric argument required\n", 2), 2);
	return (ft_atoi(p));
}

int	ft_exit_builtin(char **input, t_shell *shell)
{
	int	exit_status;

	exit_status = 0;
	if (ft_ms_count_words(input) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		shell->exit_status = 1;
	}
	else if (ft_ms_count_words(input) == 2)
		shell->exit_status = ft_convert_exitstatus(input[1]);
	exit_status = ft_ms_exit(&shell, 0);
	exit(exit_status);
}
