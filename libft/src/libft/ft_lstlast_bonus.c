/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:43:15 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:05 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/* Returns the last node of the list. */

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

//If lst->next is not NULL, it means there are more nodes in the list,
// so the function advances lst to the next node.

// int main(void)
// {
//     // Creating a linked list
//     t_list *node1 = ft_lstnew("Node 1");
//     t_list *node2 = ft_lstnew("Node 2");
//     t_list *node3 = ft_lstnew("Node 3");

//     // Linking the nodes
//     node1->next = node2;
//     node2->next = node3;

//     // Finding the last node
//     t_list *last_node = ft_lstlast(node1);

//     // Printing the content of the last node
//     if (last_node)
//         printf("Content of the last node: %s\n", (char *)last_node->content);
//     else
//         printf("List is empty!\n");

//     // Freeing allocated memory
//     free(node1);
//     free(node2);
//     free(node3);

//     return 0;
// }