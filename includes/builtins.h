/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:41:17 by codespace         #+#    #+#             */
/*   Updated: 2024/12/16 11:03:25 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# define ERROR 1

typedef struct s_env	t_env;

typedef struct s_content
{
	char	*variable;
	char	*content;
	int		has_equal;
}	t_content;

int		ft_cd(t_mini *data);
int		ft_echo(t_mini *data, t_parser *cmd);
int		ft_pwd(void);
int		ft_env(t_mini *data);
int		ft_export(t_mini *data, t_parser *cmd);
int		ft_unset(t_mini *data);
void	ft_exit(t_mini *data, t_parser *cmd);
void	bubble_sort_env_list(t_env **head);
t_env	*export_list(t_env *original);
int		call_builtin_function(t_mini *data, t_parser *cmd);
int		builtin_in_parent(char *cmd);
void	free_env_list(t_env **env);
int		separate_varcont(char *line, t_content *content);
void	fill_env_list(t_env **env_cpy, const char *variable, \
const char *content);
t_env	*env_list(char **env);
void	free_t_content(t_content *content);
int		builtin(t_mini *data, t_parser *cmd);

#endif
