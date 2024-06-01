/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:39:17 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:58:13 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/* Counts the number of nodes in a list. */

int	ft_lstsize(t_list	*lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
// int main(void)
// {
// 	// Create nodes
// 	t_list *node1 = (t_list *)malloc(sizeof(t_list));
// 	t_list *node2 = (t_list *)malloc(sizeof(t_list));
// 	t_list *node3 = (t_list *)malloc(sizeof(t_list));
// 	node1->content = "Node 1";
// 	node2->content = "Node 2";
// 	node3->content = "Node 3";

// 	// Link nodes
// 	node1->next = node2;
// 	node2->next = node3;
// 	node3->next = NULL; // Last node

// 	int size = ft_lstsize(node1); // Pass the pointer to the first node
// 	printf("Size of the list: %d\n", size);

// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }
