/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:27:23 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:59:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*substring;
	unsigned int	i;
	size_t			s_len;

	s_len = ft_strlen(s);
	i = 0;
	if (!s)
		return (NULL);
	if (start >= s_len)
		len = 0;
	if (len > s_len - start)
		len = s_len - start;
	substring = malloc(sizeof(char) * (len + 1));
	if (substring == NULL)
		return (NULL);
	while (i < len)
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

//#include <stdio.h>
//int main()
//{
//	printf("%s\n", ft_substr("norikanarimatsu", 10, 7));
//}

	//if (start >= strlen(s))
	//	return (ft_strdup(""));
