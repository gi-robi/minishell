/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:47:32 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/13 12:58:00 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

char	*env_expand(t_mini *data, char **tmp, char **string)
{
	int	j;
	int	i;

	i = data->exp_idx;
	if ((*tmp)[i] == '\0' || is_whitespace((*tmp)[i]))
		return (*tmp);
	free (*string);
	if ((*tmp)[i] == '?')
		*string = handle_question_mark(data, *tmp, i, data->exit_code);
	else
	{
		j = i;
		while ((*tmp)[j] && (*tmp)[j] != '$'
				&& !is_whitespace((*tmp)[j]) && !is_quote((*tmp)[j]))
			j++;
		*string = expand_substring(data, *tmp, i, j - 1);
	}
	free(*tmp);
	*tmp = ft_strdup(*string);
	return (*tmp);
}

void	expand_string(t_mini *data, char **string)
{
	int		single_quote;
	int		double_quote;
	char	*tmp;

	data->exp_idx = 0;
	single_quote = 0;
	double_quote = 0;
	tmp = ft_strdup(*string);
	while (tmp[data->exp_idx])
	{
		if (tmp[data->exp_idx] == '\'' && double_quote == 0)
			single_quote = !single_quote;
		else if (tmp[data->exp_idx] == '\"' && single_quote == 0)
			double_quote = !double_quote;
		else if (tmp[data->exp_idx] == '$' && single_quote == 0)
		{
			data->exp_idx++;
			tmp = env_expand(data, &tmp, string);
			continue ;
		}
		data->exp_idx++;
	}
	free(tmp);
}

void	expand_redirections(t_mini *data, t_parser *node)
{
	t_lexer	*redir;

	redir = node->redirections;
	while (redir)
	{
		if (redir->type != HERE_DOC)
			expand_string(data, &redir->token);
		redir = redir->next;
	}
}

void	expander(t_mini *data)
{
	t_parser	*tmp;
	char		**cmd_tmp;
	int			i;

	tmp = data->parser;
	while (tmp)
	{
		i = -1;
		while (tmp->commands && tmp->commands[++i])
		{
			if (!ft_strcmp(tmp->commands[i], "\"$\""))
				continue ;
			expand_string(data, &tmp->commands[i]);
		}
		expand_redirections(data, tmp);
		if (tmp->commands)
		{
			cmd_tmp = strarr_cpy(tmp->commands);
			free_strarr(tmp->commands);
			tmp->commands = cmd_tmp;
		}
		tmp = tmp->next;
	}
	clean_quotes(data);
}
