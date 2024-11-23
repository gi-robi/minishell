/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:17 by codespace         #+#    #+#             */
/*   Updated: 2024/11/20 06:22:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//el student id esta mal

#ifndef BUILTINS_H
#define BUILTINS_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../src/libft/libft.h"
#include "lexer.h"
#include "parser.h"

#define ERROR 1

typedef struct s_content
{
	char *variable;
	char *content;
	int has_equal;
} t_content;

typedef struct s_env
{
	char	*variable;
	char	*content;
	struct	s_env *next;
}	t_env;

typedef struct s_mini
{
	char		*line;
	t_env		*env;
	t_env		*export;
	t_lexer		*lexer;
	t_parser	*parser;
}	t_mini;

int pwd();
int cd(char *path, char **env);
int ft_env(t_env *envcpy);
void free_t_content(t_content *content);
void bubble_sort_env_list(t_env **head);
t_env *export_list(t_env *original);
static int doublepointerlenght(char **line);
int ft_export(t_mini *data, char **line);
void free_env_list(t_env *env);
int separate_varcont(char *line, t_content *content);
void fill_env_list(t_env **env_cpy, const char *variable, const char *content);
t_env *env_list(char **env);

#endif 