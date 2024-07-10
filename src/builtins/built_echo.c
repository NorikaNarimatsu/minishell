/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 15:46:42 by nnarimat          #+#    #+#             */
/*   Updated: 2024/07/10 13:42:57 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// This is the function to check -n flag in the input string
// -n: do not output the trailing newline
bool	is_n_flag_string(char *str)
{
	int	i;

	i = 1;
	if (str[0] != '-')
		return (false);
	while (str[i] && str[i] == 'n')
		i++;
	if (str[i] == '\0')
		return (true);
	else
		return (false);
}

// This is the function to print input based on -n status
void	echo_print_args(char **input, int idx, bool n_flag)
{
	int	i;

	i = idx;
	if (!input[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', 1);
		return ;
	}
	while (input[i])
	{
		ft_putstr_fd(input[i], 1);
		if (input[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (!n_flag)
		ft_putchar_fd('\n', 1);
}

// This is the function to execute echo
// if there is no string, just /n
// check -n flag, which can be -n or -nnn, but not -nnnna
// return 0 with success, no place for return 1.
int	echo_builtin(char **input, t_shell *shell)
{
	bool	n_flag;
	int		idx;

	(void)shell;
	n_flag = false;
	idx = 1;
	if (!input[1])
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	while (input[idx] && is_n_flag_string(input[idx]))
	{
		n_flag = true;
		idx++;
	}
	echo_print_args(input, idx, n_flag);
	return (EXIT_SUCCESS);
}
