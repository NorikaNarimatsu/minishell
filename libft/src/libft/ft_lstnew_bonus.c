/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:09:49 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:10 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
Allocates (with malloc(3)) and returns a new node.
The member variable ’content’ is initialized with
the value of the parameter ’content’. The variable
’next’ is initialized to NULL.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

// int	main(void)
// {
// 	int		content = 42;
// 	t_list	*node = ft_lstnew(&content);
// 	char	*content2 = "Norika";
// 	t_list	*node2 = ft_lstnew(content2);

// 	if (node)
// 	{
// 		printf("Node created successfully.\n");
// 		printf("Content: %d\n", *((int *)node->content));
// 		free(node);
// 	}
// 	else
// 		printf("Failed to create node.\n");
// 	if (node2)
// 	{
// 		printf("Node created successfully.\n");
// 		printf("Content: %s\n", (char *)node2->content);
// 		free(node2);
// 	}
// 	else
// 		printf("Failed to create node.\n");
// 	return (0);
// }
