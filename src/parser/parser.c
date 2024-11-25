/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 14:36:22 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/25 17:03:46 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void    print_lexer_list(t_lexer *lexer_list);	

t_lexer *store_redirection(t_lexer **token, t_parser **parser_node, t_mini *data)
{
	t_lexer	*new_node;
	char	*redirection;
	t_lexer	*new_position;

	redirection = ft_strdup((*token)->next->token);
	if (redirection == NULL)
		free_data_and_exit(data, EXIT_FAILURE);
	new_node = new_node_lexer(redirection, (*token)->type);
	if (new_node == NULL)
		free_data_and_exit(data, EXIT_FAILURE);
	new_position = (*token)->next;
	new_position = new_position->next;
	add_node_lexer(new_node, &(*parser_node)->redirections);
	delete_node_lexer(data, token);
	delete_node_lexer(data, &(*token)->next);
	return (new_position);
}

void	handle_redirections(t_mini *data, t_parser *node)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp)
	{
		if (tmp->type == PIPE)
			break ;
		if (tmp->type != WORD)
			tmp = store_redirection(&tmp, &node, data);
		else
			tmp = tmp->next;
	}
}
		  

void	store_commands(t_mini *data, t_parser **parser_node)
{
	int	cmds_num;
	int	i;
	t_lexer	*tmp;

	i = 0;
	handle_redirections(data, *parser_node);
	cmds_num = count_commands(data);
	tmp = data->lexer;
	(*parser_node)->commands = malloc(sizeof(char *) * (cmds_num + 1));
	if ((*parser_node)->commands == NULL)
		free_data_and_exit(data, EXIT_FAILURE);
	while (tmp && tmp->type != PIPE)
	{
		(*parser_node)->commands[i] = ft_strdup(tmp->token);
		if ((*parser_node)->commands[i] == NULL)
			free_data_and_exit(data, EXIT_FAILURE);
		i++;
		tmp = tmp->next;
	}
	(*parser_node)->commands[i] = NULL;
}

/*int	count_pipes(t_mini *data)
{
	int	pipes_num;
	t_lexer	*tmp;

	pipes_num = 0;
	tmp = data->lexer;
	while (tmp)
	{
		if (tmp->type == PIPE)
			pipes_num++;
		tmp = tmp->next;
	}
	return (pipes_num);
}*/

t_lexer	*remove_pipe(t_mini *data)
{
	t_lexer	*tmp;
	t_lexer	*new_position;

	new_position = NULL;
	tmp = (*data).lexer;
	while (tmp && tmp->type != PIPE)
		tmp = tmp->next;
	if (tmp && tmp->type == PIPE)
	{
		new_position = tmp->next;
		delete_node_lexer(data, &tmp);
	}
	return (new_position);
}
void	parser(t_mini *data)
{
	t_parser	*node;
	t_parser	*parser;

	node = NULL;
	parser = NULL;
//	if (unexpected_token_error(error_check(data)))
//		return ;
	while (data->lexer)
	{
		node = new_node_parser();
		if (node == NULL)
			free_data_and_exit(data, EXIT_FAILURE);
		store_commands(data, &node);
		add_node_parser(node, &parser);
		data->lexer = remove_pipe(data);
	}
	data->parser = parser;
}
