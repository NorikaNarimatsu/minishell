/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:15:40 by nnarimat          #+#    #+#             */
/*   Updated: 2024/05/04 17:00:53 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	void	*res;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		res = malloc(0);
		if (!res)
			return (0);
		return (res);
	}
	if ((nmemb * size) / size != nmemb)
		return (0);
	res = malloc(nmemb * size);
	if (!res)
		return (0);
	i = 0;
	while (i < nmemb * size)
	{
		((char *)res)[i] = '\0';
		i++;
	}
	return (res);
}

size_t	ft_strlen_gnl(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_pos(char *str, int c)
{
	int	pos;

	pos = 0;
	if (!str)
		return (-1);
	while (str[pos] != '\0')
	{
		if ((unsigned char)str[pos] == (unsigned char)c)
			return (pos + 1);
		pos++;
	}
	return (-1);
}

char	*ft_strdup_gnl(char *str)
{
	char	*rem;
	int		pos;
	int		i;

	i = 0;
	pos = ft_pos(str, '\n');
	rem = ft_calloc_gnl((ft_strlen_gnl(str) - pos + 1), sizeof(char));
	if (!rem || !str)
		return (NULL);
	while (str[pos] != '\0' && BUFFER_SIZE > pos)
		rem[i++] = str[pos++];
	if (ft_strlen_gnl(rem) == 0)
		return (ft_fn(&rem), NULL);
	return (rem);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	len_s1;
	size_t	size_nl;
	char	*output;

	len_s1 = ft_strlen_gnl(s1);
	size_nl = 0;
	if (ft_pos(s2, '\n') == -1)
		size_nl = ft_strlen_gnl(s2);
	else
		size_nl = ft_pos(s2, '\n');
	output = ft_calloc_gnl((len_s1 + size_nl + 1), sizeof(char));
	if (!output)
		return (ft_fn(&s1), NULL);
	len_s1 = 0;
	if (s1)
	{
		while (s1[len_s1] != '\0')
		{
			output[len_s1] = s1[len_s1];
			len_s1++;
		}
	}
	while (*s2 && size_nl-- > 0)
		output[len_s1++] = *s2++;
	return (ft_fn(&s1), output);
}
