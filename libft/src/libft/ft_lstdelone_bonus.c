/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 14:07:47 by nnarimat          #+#    #+#             */
/*   Updated: 2024/04/02 16:57:16 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
Takes as a parameter a node and frees the memory of
the node’s content using the function ’del’ given
as a parameter and free the node. The memory of
’next’ must not be freed.

del: A function pointer that points to a function
     responsible for freeing the content of the node.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!del)
		return ;
	if (lst)
	{
		(*del)(lst->content);
		free(lst);
	}
}
//valgrind ./a.out
// int	main(void)
// {
// 	t_list *node = (t_list *)malloc(sizeof(t_list));
// 	int *data = (int *)malloc(sizeof(int));
// 	*data = 42;

// 	// Assign the integer to the node's content
// 	node->content = data;
// 	// Set next pointer to NULL
// 	node->next = NULL;
// 	ft_lstdelone(node, delete_int);

// 	return 0;
// }
