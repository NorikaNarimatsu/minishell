/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/13 16:58:53 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:22 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	find_first_index(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[i]) == 0)
			break ;
		i++;
	}
	return (i);
}

static int	find_last_index(const char *s1, const char *set)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(s1);
	i = 0;
	while (i < len)
	{
		if (ft_strchr(set, s1[len - i -1]) == 0)
			break ;
		i++;
	}
	return (len - i);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	int		i_first;
	int		i_last;
	int		len;
	char	*trim;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i_first = find_first_index(s1, set);
	i_last = find_last_index(s1, set);
	len = i_last - i_first;
	if (len < 0)
		len = 0;
	trim = malloc(sizeof(char) * (len + 1));
	if (trim == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trim[i] = s1[i + i_first];
		i++;
	}
	trim[i] = '\0';
	return (trim);
}

//#include <stdio.h>
//#include <stdlib.h>

//int main(void) {
//	const char str[] = "aacca";
//	const char set[] = "ac";
//	char *result;

//	result = ft_strtrim(str, set);

//	if (result)
//	{
//		printf("%s\n", result);
//		free(result);
//	}
//	else
//	{
//		printf("Memory allocation failed.\n");
//	}

//    return 0;
//}
