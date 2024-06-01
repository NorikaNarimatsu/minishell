/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 13:55:58 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:50 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
Adds the node ’new’ at the end of the list.
*/

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (lst)
	{
		if (*lst)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
		else
			*lst = new;
	}
}

// int main(void)
// {
// 	// Create an empty list
// 	t_list *head = NULL;

// 	// Create new nodes
// 	t_list *node1 = (t_list *)malloc(sizeof(t_list));
// 	node1->content = "Node 1";
// 	node1->next = NULL;

// 	t_list *node2 = (t_list *)malloc(sizeof(t_list));
// 	node2->content = "Node 2";
// 	node2->next = NULL;

// 	t_list *node3 = (t_list *)malloc(sizeof(t_list));
// 	node3->content = "Node 3";
// 	node3->next = NULL;

// 	// Add nodes to the back of the list
// 	ft_lstadd_back(&head, node1);
// 	// Print the list
// 	printf("List after adding nodes to the back 1:\n");
// 	print_list(head);
// 	ft_lstadd_back(&head, node2);
// 	// Print the list
// 	printf("List after adding nodes to the back 2:\n");
// 	print_list(head);
// 	ft_lstadd_back(&head, node3);

// 	// Print the list
// 	printf("List after adding nodes to the back 3:\n");
// 	print_list(head);

// 	// Free allocated memory
// 	free(node1);
// 	free(node2);
// 	free(node3);

// 	return 0;
// }
