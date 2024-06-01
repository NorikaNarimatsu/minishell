/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:56:46 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:50 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

char	*ft_strdup(const char	*s)
{
	char	*t;
	size_t	len;

	len = ft_strlen(s);
	t = malloc(sizeof(char) * (len + 1));
	if (t == NULL)
		return (NULL);
	else
		ft_strlcpy(t, s, len + 1);
	return (t);
}

/*
//Do I need to type cast malloc?
#include <string.h>
#include <stdio.h>

int	main(void)
{
	char	*s;
	char	*t;

	s = strdup("Norika");
	printf("s = %s\n", s);
	t = ft_strdup("Norika");
	printf("t = %s\n", t);

	free(s);
	free(t);

	return (0);
}
*/
