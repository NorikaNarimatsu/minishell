/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 10:11:20 by nnarimat          #+#    #+#             */
/*   Updated: 2024/05/20 11:17:25 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

static int	ft_string_count(char const *s, char c)
{
	int	count;

	if (*s == '\0')
		return (0);
	if (s[0] != c)
		count = 1;
	else
		count = 0;
	s++;
	while (*s)
	{
		if (*s == c)
			s++;
		else if (*(s - 1) != c)
			s++;
		else
		{
			s++;
			count++;
		}
	}
	return (count);
}

static char	*ft_place_word(const char *str, int start, int end)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((end - start + 1) * sizeof(char));
	if (!word)
		return (0);
	while (start < end)
		word[i++] = str[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_free_all(char **array, int j)
{
	j = 0;
	while (array[j] != NULL)
	{
		free(array[j]);
		j++;
	}
	free(array);
	return (NULL);
}

static int	ft_word_len(char const	*s, char c, int i)
{
	size_t	word_len;

	word_len = 0;
	while (s[i + word_len] != c && (i + word_len) < ft_strlen(s))
		word_len++;
	return (word_len);
}

char	**ft_split(char const	*s, char c)
{
	char	**final;
	size_t	i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (0);
	final = malloc((ft_string_count(s, c) + 1) * sizeof(char *));
	if (!final)
		return (0);
	while (i < ft_strlen(s))
	{
		if (s[i] != c)
		{
			final[j++] = ft_place_word(s, i, (i + ft_word_len(s, c, i)));
			if (final[j - 1] == NULL)
				return (ft_free_all(final, j - 1));
			i = i + ft_word_len(s, c, i);
		}
		else if (s[i] == c)
			i++;
	}
	final[ft_string_count(s, c)] = NULL;
	return (final);
}

/*
//int	main(void)
//{
//	char		**final;
//	char const	*s;
//	char		c;

//	//s = "--1-2--3---4----5-----42";
//	s = "  tripouille  42  ";
//	c = ' ';
//	final = ft_split(s, c);
//	//printf("FINAL :\n %s\n %s \n %s \n %s \n",
//	//	final[0], final[1], final[2], final[3]);

//	return (0);
//}

// Useful printout
//printf("Count is %d \n", word_count);
//printf("start:  %d\t end:  %d\t  len: %d\n", start,
	(start + word_len - 1), word_len);
//printf("j is %d and our string is %s\n", j, final[j]);
*/
