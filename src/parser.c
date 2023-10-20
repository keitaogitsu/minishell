/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/20 21:48:00 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*pop_token(t_token_list **list)
{
	char	*value;

	if (!(*list))
		return (NULL);
	value = (*list)->token;
	*list = (*list)->next;
	return (value);
}

static int	updata_type_value(t_node *node, \
		t_token_list **list, t_parse_check *key)
{
	if (!key->key_type)
	{
		key->key_type = true;
		node->type = N_PYPE;
		node->value = key->token;
		key->key_list = *list;
	}
	else
	{
		node->right = parser(node->right, &key->key_list, key);
		return (1);
	}
	return (0);
}

static t_node	*redir_parse(t_node *node, t_token_list **list, t_parse_check *key)
{
	all_node_init(node);
	node->left->value = node->value;
	node->value = key->token;
	node->type = N_REDIR_IN;
	while (*list)
	{
		key->token = pop_token(list);
		if (ft_strcmp(key->token, "|") == 0)
			break ;
		if (ft_strcmp(key->token, "<") == 0)
		{
			node->left = redir_parse(node->left, list, key);
			break ;
		}
		node->right->value = my_strjoin(node->right->value, key->token);
		node->right->value = my_strjoin(node->right->value, " ");
	}
	return (node);
}
static t_node	*updata_name_value(t_node *node, t_parse_check *key, t_token_list **list)
{
	if (key->key_type)
	{
		node->right->type = N_COMMAND;
		node->right->value = my_strjoin(node->right->value, key->token);
		node->right->value = my_strjoin(node->right->value, " ");
	}
	else if (!key->key_type)
	{
		if (ft_strcmp(key->token, "<") == 0)
		{
			key->key_redir = true;
			node->left = redir_parse(node->left, list, key);
		}
		else
		{
			node->left->type = N_COMMAND;
			node->left->value = my_strjoin(node->left->value, key->token);
			node->left->value = my_strjoin(node->left->value, " ");
		}
	}
	return (node);
}

t_node	*parser(t_node *node, t_token_list **list, t_parse_check *key)
{
	all_node_init(node);
	if (!node)
		return (NULL);
	key->key_type = false;
	key->key_redir = false;
	while (*list)
	{
		if (!key->key_redir)
			key->token = pop_token(list);
		if (key->key_redir)
			key->key_redir = false;
		if (!key->token)
			return (NULL);
		if (ft_strcmp(key->token, "|") == 0)
		{
			if (updata_type_value(node, list, key) == 1)
				break ;
		}
		else
			node = updata_name_value(node, key, list);
	}
	if (!node->value)
	{
		node->value = node->left->value;
		node->left->value = NULL;
	}
	return (node);
}

t_node	*parser_start(t_token_list **list)
{
	t_node			*node;
	t_parse_check	*key;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	key = (t_parse_check *)malloc(sizeof(t_parse_check));
	if (!key)
		return (NULL);
	node = parser(node, list, key);
	print_node(node);
	free(key);
	return (node);
}
