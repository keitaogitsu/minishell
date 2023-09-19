/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:52 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/19 08:39:11 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	get_args(char *line)
{
	char	**input;
	size_t		i;

	input = ft_split(line, SPACE);
	if (!input)
		return (1);
	return (0);
}

void	bash_loop(void)
{
	char	*line;
	int		flag;

	flag = 0;
	while (flag == 0)
	{
		line = readline(MINISHELL);
		if (!line)
			flag = 1;
		else if (line[0] == '\0')
			free(line);
		else
		{
			add_history(line);
//				flag = 1;
			t_node	*tree = tokenizeAndParse(line);
			printf("top_type %d\nleft_type %d\n right_type %d\n%s\nr %s\nl %s\n", tree->type, tree->left->type, tree->right->type, tree->name, tree->right->name, tree->left->name);
			tree = tree->right;
			printf("\n\n");
			printf("top_type %d\nleft_type %d\n right_type %d\n%s\nr %s\nl %s\n", tree->type, tree->left->type, tree->right->type, tree->name, tree->right->name, tree->left->name);
			free(line);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc == 1)
		bash_loop();
	return (0);
}
