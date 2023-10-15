/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/10/16 00:19:12 by fwatanab         ###   ########.fr       */
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
		node->right->value = key->token;
		node->right->type = N_PYPE;
		node->right = parser(node->right, &key->key_list, key);
		return (1);
	}
	return (0);
}

static void	updata_name_value(t_node *node, char *token, bool key_type)
{
	if (key_type)
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

t_node	*parser(t_node *node, t_token_list **list, t_parse_check *key)
{
	node = all_node_init();
	if (!node)
		return (NULL);
	key->key_type = false;
	while (*list)
	{
		key->token = pop_token(list);
		if (!key->token)
			return (NULL);
		if (ft_strcmp(key->token, "|") == 0)
		{
			if (updata_type_value(node, list, key) == 1)
				break ;
		}
		else
			updata_name_value(node, key->token, key->key_type);
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

	key = (t_parse_check *)malloc(sizeof(t_parse_check));
	if (!key)
		return (NULL);
	node = parser(node, list, key);
	print_node(node);
	free(key);
	return (node);
}
