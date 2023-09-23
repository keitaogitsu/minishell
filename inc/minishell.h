/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/19 14:46:54 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stddef.h>
# include <stdbool.h>

# define MINISHELL "minishell $ "
# define SPACE ' '
# define D_QUOTE '"'
# define S_QUOTE '\''
# define PYPE '|'
# define REDIR_IN '<'
# define REDIR_OUT '>'
# define REDIR_HIRE "<<"
# define REDIR_APPEND ">>"

//tokenize
//typedef struct s_parser_result
//{
//	const char	*str;
//	const char	*start:
//}	t_parser_result;

typedef struct s_command
{
	char				*token;
	struct s_command	*next;
}	t_command;

//typedef enum e_type
//{
//	CMD,
//	REDIR_IN,
//	REDIR_OUT,
//	REDIR_HERE,
//	REDIR_APPEND,
//	PIPE
//}	t_type;

typedef struct s_node
{
//	enum e_type		type;
	char			*name;
	char			*option;
	char			**args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

int		syntax_analysis(char *line);

//utils
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strstr(const char *big, const char *little);

#endif
