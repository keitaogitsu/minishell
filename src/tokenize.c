/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:13:37 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/23 14:44:36 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_command *add_token(t_command **list, char *token)
{
	t_command	*new_node;
	t_command	*tmp;

	new_node = (t_command *)malloc(sizeof(t_command));
	if (!new_node)
		return (NULL);
	new_node->token = ft_strdup(token);
	new_node->next = NULL;
	if (*list == NULL)
		*list = new_node;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	return (new_node);
}

static const char	*handle_token(const char *str, const char *start, t_command **head)
{
	char	*token;

	if (str > start)
	{
		token = strndup(start, str - start);
		add_token(head, token);
		free(token);
	}
	str++;
	token = ft_strndup(str - 1, 1);
	add_token(head, token);
	free(token);

	return (str);
}

static const char	*check_cmd_type(const char *str, const char *start, bool s_quote, bool d_quote, t_command *head)
{
	while (*str)
	{
		if (!d_quote && *str == D_QUOTE)
			d_quote = true;
		else if (!d_quote && *str == S_QUOTE)
			s_quote = true;
		else if (d_quote && *str == D_QUOTE)
		{
			str++;
			break ;
		}
		else if (!d_quote && !s_quote && *str == SPACE)
			break ;
		else if (!d_quote && !s_quote && (*str == PYPE
					|| *str == REDIR_IN || *str == REDIR_OUT))
		{
			str = handle_token(str, start, &head);
			start = str;/////   <---
			break ;
		}
		str++;
	}
	return (str);
}

static t_command	*tokenize(const char *str)
{
	t_command	*head;
	const char	*start;
	char		*token;
	bool		d_quote;
	bool		s_quote;

	head = NULL;
	while (*str)
	{
		while (*str == SPACE)
			str++;
		start = str;
		d_quote = false;
		s_quote = false;
		str = check_cmd_type(str, start, s_quote, d_quote, head);
		if (str > start)
		{
			token = strndup(start, str - start);
			add_token(&head, token);
			free(token);
		}
	}
	return (head);
}

int	syntax_analysis(char *line)
{
	t_command	*cmd;

	cmd = tokenize(line);
	if (!cmd)
		return (1);
	while (cmd)
	{
		printf("token > %s\n", cmd->token);
		cmd = cmd->next;
	}
	return (0);
}

