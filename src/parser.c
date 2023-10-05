/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/05 15:39:53 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//t_node	create_syntax_tree(t_token_list *list)
//{
//	t_node	*node;
//
//	node = (t_node *)malloc(sizeof(t_node));
//	if (!node)
//		return (NULL);
//	while (*list)
//	{
//		list++;
//	}
//	return (node);
//}
//
//t_node	*parse_command(t_token_list *list)
//{
//	while (*list)
//	{
//		if (*list->token == PYPE)
//		token++;
//	}
//}

char	*pop_token(t_token_list **list)
{
	char	*value;

	if (!(*list))
	    return (NULL);
	value = (*list)->token;
	*list = (*list)->next;
	return (value);
}

t_node	*node_init(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->value = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node	*parser(t_node *node, t_token_list **list)
{
	t_node			*head;
	t_token_list	*start;
	char			*token;
	bool			key_type;

	node = node_init();
	if (!node)
		return (NULL);
	node->left = node_init();
	if (!node->left)
		return (NULL);
	node->right = node_init();
	if (!node->right)
		return (NULL);
	head = node;
	key_type = false;
	while (*list)
	{
		token = pop_token(list);
		if (!token)
			return (NULL);
		if (ft_strcmp(token, "|") == 0 && !key_type)
		{
			key_type = true;
			node->type = N_PYPE;
			node->value = token;
			start = *list;
		}
		else if (ft_strcmp(token, "|") == 0)
		{
			node->right->value = token;
			node->right->type = N_PYPE;
			node->right = parser(node->right, &start);
			break ;
		}
		else if (key_type)
		{
			node->right->type = N_COMMAND;
			node->right->value = my_strjoin(node->right->value, token);
			node->right->value = my_strjoin(node->right->value, " ");
		}
		else if (!key_type)
		{
			node->right->type = N_COMMAND;
			node->left->value = my_strjoin(node->left->value, token);
			node->left->value = my_strjoin(node->left->value, " ");
		}
	}
	if (!node->value)
	{
		node->value = node->left->value;
		node->left->value = NULL;
	}
	return (head);
}

void	print_node(t_node *node)
{
	while (node->right)
	{
		printf("node_left-> %s\n", node->left->value);
		printf("node_value-> %s\n", node->value);
		printf("node_type-> %u\n", node->type);
		printf("node_right-> %s\n", node->right->value);
		printf("------------------\n");
		node = node->right;
	}
}

t_node	*parser_start(t_token_list **list)
{
	t_node	*node;

	node = parser(node, list);
	print_node(node);
	return (node);
}
