/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnarimat <nnarimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:25:24 by nnarimat          #+#    #+#             */
/*   Updated: 2024/03/28 13:57:53 by nnarimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
Adds the node ’new’ at the beginning of the list.
*/

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (lst)
	{
		if (*lst)
			new->next = *lst;
		*lst = new;
	}
}

// int	main(void)
// {
// 	t_list *head = NULL;
// 	t_list *node1 = (t_list *)malloc(sizeof(t_list));
// 	node1->content = "Node 1";
// 	node1->next = NULL;
// 	t_list *node2 = (t_list *)malloc(sizeof(t_list));
// 	node2->content = "Node 2";
// 	node2->next = NULL;
// 	t_list *node3 = (t_list *)malloc(sizeof(t_list));
// 	node3->content = "Node 3";
// 	node3->next = NULL;

// 	ft_lstadd_front(&head, node1);
// 	ft_lstadd_front(&head, node2);
// 	ft_lstadd_front(&head, node3);

// 	printf("List after adding nodes to the front:\n");
// 	print_list(head);

// 	free(node1);
// 	free(node2);
// 	free(node3);
// 	return (0);
// }
