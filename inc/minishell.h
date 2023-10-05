/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/29 18:36:59 by fwatanab         ###   ########.fr       */
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

typedef struct s_token_list
{
	char				*token;
	struct s_token_list	*next;
}	t_token_list;

typedef enum e_type
{
	N_COMMAND,
	N_REDIR_IN,
	N_REDIR_OUT,
	N_REDIR_HERE,
	N_REDIR_APPEND,
	N_PYPE
}	t_type;

typedef struct s_node
{
	enum e_type		type;
	char			*value;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

int		syntax_analysis(char *line);
t_node	*parser_start(t_token_list **list);

//utils
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strstr(const char *big, const char *little);
int		ft_strcmp(const char *s1, const char *s2);
char	*my_strjoin(char const *s1, char const *s2);

#endif
