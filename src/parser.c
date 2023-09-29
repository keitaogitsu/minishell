/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:19:00 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/29 18:41:56 by fwatanab         ###   ########.fr       */
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
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	while (*list && ft_strcmp((*list)->token, "|") == 0)
	{
	}
	return (node);
}
