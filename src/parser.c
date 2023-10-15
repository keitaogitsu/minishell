/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/15 14:24:55 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

t_node	*all_node_init(void)
{
	t_node	*node;

	node = node_init();
	if (!node)
		return (NULL);
	node->left = node_init();
	if (!node->left)
	{
		free(node);
		free(node->left);
		return (NULL);
	}
	node->right = node_init();
	if (!node->right)
	{
		free(node);
		free(node->left);
		return (NULL);
	}
	return (node);
}

//t_node	*redir_parse(t_node *node, t_token **list)
//{
//	char	*token;
//
//	while (*list)
//	{
//		token = pop_token(list);
//		if (!token)
//			return (NULL);
//		if (ft_strcmp(token, "<") == 0 || ft_strcmp(token, ">") == 0)
//	}
//	return (node);
//}

bool	check_type(t_token_list *start, t_token_list *list)
{
	t_token_list	*tmp;

	tmp = start;
	while (tmp->next && ft_strcmp(tmp->token,  "|") != 0)
	{
		if (start == list)
			break ;
		if (ft_strcmp(tmp->token,  "<") == 0 || ft_strcmp(tmp->token,  ">") == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

t_node	*parser(t_node *node, t_token_list **list, char *type, t_type n_type)
{
	t_token_list	*key_list;
	char			*token;
	bool			key_type;

	node = all_node_init();
	if (!node)
		return (NULL);
	key_type = false;
	while (*list)
	{
		token = pop_token(list);
		if (!token)
			return (NULL);
		if (ft_strcmp(token, type) == 0 && !key_type)
		{
			key_type = true;
			node->type = n_type;
			node->value = token;
			key_list = *list;
		}
		else if (ft_strcmp(token, type) == 0)
		{
			node->right->value = token;
			node->right->type = n_type;
			node->right = parser(node->right, &key_list, type, n_type);
			break ;
		}
//		else if (ft_strcmp(token, "<") == 0)
//		{
//			node->left->value = token;
//			node->left->type = N_REDIR_IN;
//			node->left = parser(node->left, &key_list, type, n_type);
//			break ;
//		}
		else if (key_type)
		{
			node->right->type = N_COMMAND;
			node->right->value = my_strjoin(node->right->value, token);
			node->right->value = my_strjoin(node->right->value, " ");
		}
		else if (!key_type)
		{
			node->left->type = N_COMMAND;
			node->left->value = my_strjoin(node->left->value, token);
			node->left->value = my_strjoin(node->left->value, " ");
		}
	}
	if (!node->value)
	{
		node->value = node->left->value;
		node->left->value = NULL;
	}
	return (node);
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

t_node	*parser_start(t_token_list **list)
{
	t_node	*node;

	node = parser(node, list, "|", N_PYPE);
	print_node(node);
	return (node);
}
