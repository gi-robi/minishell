/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:48:36 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/25 15:48:28 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
#define MINI_H

#include "lexer.h"
#include "parser.h"
#include "strarr_utils.h"
#include "str_utils.h"
#include "utils.h"
#include "executor.h"
#include "builtins.h"
#include "../libs/libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>

typedef struct s_env
{
	char	*variable;
	char	*content;
	struct	s_env *next;
}	t_env;

typedef struct s_mini
{
	char		*line;
	char		**env;
	t_lexer		*lexer;
	t_parser	*parser;
	int			*pids;
	int		in_fd;
	t_env		*env_list;
}	t_mini;

void    mini_loop(t_mini *data);
int is_whitespace(char c);


#endif
