/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:13:37 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/19 14:50:11 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_command	*tokenize(char *str)
{
	t_command	*head;
	const char	*start;
	bool		d_quote;
	bool		s_quote;
	char		*token;
	size_t		i;

	head = NULL;
	while (str[i])
	{
		while (str[i] == SPACE)
			i++;
		start = str;
		d_quote = false;
		s_quote = false;
		while (str[i])
		{
			if (!d_quote && str[i] == D_QUOTE)
				d_quote = true;
			else if (!d_quote && str[i] == S_QUOTE)
				s_quote = true;
			else if (!d_quote && !s_quote && str[i] == SPACE)
				break ;
			i++;
		}
		if (str > start)
		{
			token = strndup(start, str - start);
			printf("%s\n", token);
//			add_token(&head, token);
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
//	while (cmd)
//	{
//		printf("token > %s\n", cmd->token);
//		cmd = cmd->next;
//	}
	return (0);
}

t_node	*create_node(t_type type, char *name, char **args)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		exit(EXIT_FAILURE);
	node->type = type;
	node->name = name;
	node->args = args;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_node *tokenizeAndParse(const char *cmd) {
    if (!cmd) return NULL;

    // | にのみ
    char *pipe_pos = ft_strstr(cmd, "|");
	printf("line > %s\n", pipe_pos);
    if (pipe_pos) {
		ptrdiff_t diff = pipe_pos - cmd;
        char *left_cmd = ft_strndup(cmd, diff);
		printf("size_t > %td\n", diff);
		printf("left > %s\n", left_cmd);
        char *right_cmd = ft_strdup(pipe_pos + 1);
		printf("right > %s\n", right_cmd);

        t_node *left_node = tokenizeAndParse(left_cmd);
        t_node *right_node = tokenizeAndParse(right_cmd);

        t_node *pipe_node = create_node(PIPE, NULL, NULL);
        pipe_node->left = left_node;
        pipe_node->right = right_node;

        free(left_cmd);
        free(right_cmd);

        return pipe_node;
    } else {
        // ここではコマンドと引数を分離する簡単な実装を行います
        // 実際にはより詳細な解析が必要です
        char *name = strdup(cmd);  // ここを改良してコマンド名だけを取得するようにすること
        char **args = NULL;  // 実際には引数の解析と分割を行う必要があります

        return create_node(CMD, name, args);
    }
}
