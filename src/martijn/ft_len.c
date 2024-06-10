/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_len.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mdraper <mdraper@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/05 15:11:18 by mdraper       #+#    #+#                 */
/*   Updated: 2024/06/10 12:18:49 by mdraper       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lenword(char *str)
{
	int	i;

	i = 0;
	if (!str || ft_isword(str[i]) == 0)
		return (i);
	while (ft_isword(str[i]))
		i++;
	return (i);
}

int	ft_lenredirection(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	i = ft_istworedirection(str);
	if (i == 0)
		i = ft_isoneredirection(str[i]);
	return (i);
}

int	ft_lenpipe(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (i);
	i = ft_ispipe(str[i]);
	return (i);
}

int	ft_lensquote(char *str)
{
	int	quote;
	int	i;

	i = 0;
	if (!str || ft_issquote(str[i]) == 0)
		return (i);
	quote = 1;
	i++;
	while (str[i])
	{
		if (ft_issquote(str[i]) == 1)
		{
			quote++;
			break ;
		}
		i++;
	}
	if (quote == 1)
	{
		printf("ERROR! - Single single quote\n");
		return (0);
	}
	return (i + 1);
}

int	ft_lendquote(char *str)
{
	int	quote;
	int	i;

	i = 0;
	if (!str || ft_isdquote(str[i]) == 0)
		return (i);
	quote = 1;
	i++;
	while (str[i])
	{
		if (ft_isdquote(str[i]) == 1)
		{
			quote++;
			break ;
		}
		i++;
	}
	if (quote == 1)
	{
		printf("ERROR! - Single double quote\n");
		return (0);
	}
	return (i + 1);
}
