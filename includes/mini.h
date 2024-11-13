/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 13:48:36 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/13 10:52:49 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
#define MINI_H

#include "lexer.h"
#include "parser.h"
#include "strarr_utils.h"
#include "str_utils.h"
#include "utils.h"
#include "../libs/libft/libft.h"
#include <stdio.h>

typedef struct s_mini
{
	char		*line;
	char		**env;
	t_lexer		*lexer;
	t_parser	*parser;
}	t_mini;

void    mini_loop(t_mini *data);
int is_whitespace(char c);

#endif
