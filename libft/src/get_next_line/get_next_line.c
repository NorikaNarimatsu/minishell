/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 20:15:26 by nnarimat          #+#    #+#             */
/*   Updated: 2024/05/04 21:47:03 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_fn(char **ptr)
{
	if (*ptr)
	{
		free (*ptr);
		*ptr = NULL;
	}
}

char	*ft_read_file(int fd, char **line, char **rem, char *buf)
{
	int			read_count;

	read_count = 1;
	while (ft_pos(buf, '\n') == -1 && read_count != 0)
	{
		read_count = read(fd, buf, BUFFER_SIZE);
		if (read_count == -1)
			return (ft_fn(&buf), NULL);
		else if (read_count == 0)
			return (ft_fn(rem), ft_fn(&buf), *line);
		buf[read_count] = '\0';
		if (ft_pos(buf, '\n') == -1)
			*line = ft_strjoin_gnl(*line, buf);
		else
		{
			*line = ft_strjoin_gnl(*line, buf);
			if (!*line)
				return (ft_fn(rem), ft_fn(&buf), NULL);
			*rem = ft_strdup_gnl(buf);
			if (ft_pos(buf, '\n') != (int)ft_strlen_gnl(buf) && !*rem)
				return (ft_fn(line), ft_fn(&buf), NULL);
		}
	}
	return (ft_fn(&buf), *line);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	char		*buf;
	static char	*rem;

	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, NULL, 0) == -1)
		return (ft_fn(&rem), NULL);
	if (rem)
	{
		if (ft_pos(rem, '\n') != -1)
		{
			tmp = rem;
			line = ft_strjoin_gnl(line, rem);
			if (!line)
				return (ft_fn(&rem), NULL);
			return (rem = ft_strdup_gnl(rem), ft_fn(&tmp), line);
		}
		line = rem;
		rem = NULL;
	}
	buf = (char *)ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buf)
		return (ft_fn(&line), NULL);
	return (ft_read_file(fd, &line, &rem, buf));
}

// # include <stdio.h>
// # include <fcntl.h>
// int	main(void)
// {
// 	int		fd;
// 	int		count;
// 	char	*line;

// 	count = 0;
// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("Error");
// 		return (1);
// 	}
// 	while (count < 13)
// 	{
// 		line = get_next_line(fd);
// 		count++;
// 		printf("\n[%d]: %s\n", count, line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }
