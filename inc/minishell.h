/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/24 19:37:17 by fwatanab         ###   ########.fr       */
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
	N_PIPE
}	t_type;

typedef struct s_node
{
	enum e_type		type;
//	char			*name;
	char			**value;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

int		syntax_analysis(char *line);

//utils
char	*ft_strndup(const char *s1, size_t n);
char	*ft_strstr(const char *big, const char *little);

#endif
