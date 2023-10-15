/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 00:21:46 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/16 00:21:47 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_list(t_token_list *list)
{
	while (list)
	{
		printf("list-> %s\n", list->token);
		list = list->next;
	}
	printf("------------------\n\n");
}

void	print_node(t_node *node)
{
	while (node->right)
	{
		printf("node_value-> %s\n", node->value);
		printf("node_type-> %u\n\n", node->type);
		printf("node_left-> %s\n", node->left->value);
		printf("node_left_type-> %u\n\n", node->left->type);
		printf("node_right-> %s\n", node->right->value);
		printf("node_right_type-> %u\n\n", node->right->type);
		printf("------------------\n");
		node = node->right;
	}
}
