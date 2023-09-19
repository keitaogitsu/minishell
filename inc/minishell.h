/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fwatanab <fwatanab@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 21:17:45 by fwatanab          #+#    #+#             */
/*   Updated: 2023/09/18 21:17:46 by fwatanab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MINISHELL "minishell $ "
# define SPACE ' '
# define D_QUOTE '"'

typedef enum e_type
{
	CMD,
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HERE,
	PIPE
}	t_type;

typedef struct s_node
{
	enum e_type		type;
	char			*name;
	char			**args;
	struct s_node	*left;
	struct s_node	*right;
}	t_node;

t_node	*tokenizeAndParse(const char *cmd);

//utils
char	*ft_strndup(const char *s1, size_t n);

#endif
