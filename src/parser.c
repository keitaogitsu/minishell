/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/27 19:01:44 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_node	create_syntax_tree(t_token_list *list)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	while (*list)
	{
		list++;
	}
	return (node);
}

t_node	*parse_command(t_token_list *list)
{
	while (*list)
	{
		if (*list->token == PYPE)
		token++;
	}
}

char	*pop(t_token_list **list)
{
	char	*value;

	if (!(*list))
	    return (NULL);
	value = (*list)->token;
	*list = (*list)->next;
	return (value);
}

t_node	*parse_pipeline(t_token_list **list)
{
	char	*token;

	if (!list)
		return (node);
	token = pop(list);
	if (*list->list == PYPE)
	{
		node->value = token;
		node->typw = N_TYPE;
	}
	else
	{
		node->right->
	}
	return (node);
}
