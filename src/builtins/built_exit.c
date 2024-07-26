/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   built_exit.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: nnarimat <nnarimat@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/07/10 11:38:52 by nnarimat      #+#    #+#                 */
/*   Updated: 2024/07/26 22:04:52 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_convert_exitstatus(char *p)
{
	int	exit_status;
	int	i;

	i = 0;
	exit_status = 0;
	if ((p[0] != '-' && p[0] != '+' && !ft_isdigit(p[0]))
		|| ((p[0] == '-' || p[0] == '+') && !ft_isdigit(p[1])))
		return (ft_putstr_fd("exit: numeric argument required\n", 2), 2);
	else
	{
		while (p[i] != '\0')
		{
			if (!ft_isdigit(p[i]) && p[i] != '-' && p[i] != '+')
			{
				ft_putstr_fd("exit: numeric argument required\n", 2);
				return (2);
			}
			i++;
		}
		if (exit_status == 0)
			return (ft_atoi(p));
	}
	return (0);
}

int	ft_exit_builtin(char **input)
{
	int		exit_status;

	printf("exit\n");
	exit_status = 0;
	if (ft_ms_count_words(input) > 2)
		return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	if (ft_ms_count_words(input) == 2)
	{
		exit_status = ft_convert_exitstatus(input[1]);
		if (input[2])
			return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	}
	exit(exit_status);
}

/*

int	ft_exit_builtin(char **input)
{
	int		exit_status;
	int		i;
	char	*p;

	exit_status = 0;
	i = 0;
	p = input[1];
	printf("exit\n");
	if (input[1])
	{
		if ((p[0] != '-' && p[0] != '+' && !ft_isdigit(p[0]))
			|| ((p[0] == '-' || p[0] == '+') && !ft_isdigit(p[1])))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			exit_status = 2;
		}
		else
		{
			while (p[i] != '\0')
			{
				if (!ft_isdigit(p[i]) && p[i] != '-' && p[i] != '+')
				{
					ft_putstr_fd("exit: numeric argument required\n", 2);
					exit_status = 2;
					break ;
				}
				i++;
			}
			if (exit_status == 0)
				exit_status = ft_atoi(input[1]);
		}
		if (input[2])
			return (ft_putstr_fd("exit: too many arguments\n", 2), 1);
	}
	exit(exit_status);
}

*/