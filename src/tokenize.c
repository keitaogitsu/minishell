/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 00:13:37 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/19 10:18:04 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

//void	do_tokenize(char *line)
//{
//	t_node	*node;
//	size_t	i;
//
//	node = (t_node *)malloc(sizeof(t_node));
//	if (!node)
//		return ;
//	i = 0;
//	while (line[i])
//}

t_node	*create_node(t_type type, char *name, char **args)
{
	t_node *node = malloc(sizeof(t_node));
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

    // | にのみ焦点を当てます
    char *pipe_pos = ft_strnstr(cmd, "|", ft_strlen(cmd));
    if (pipe_pos) {
		printf("size = %ld\n", pipe_pos - cmd);
        char *left_cmd = ft_strndup(cmd, pipe_pos - cmd);
        char *right_cmd = ft_strdup(pipe_pos + 1);

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
