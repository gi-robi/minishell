/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils_lexer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:51:06 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/10 13:25:40 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	free_node_lexer(t_lexer **node)
{
	if ((*node) && (*node)->token)
	{
		free((*node)->token);
		(*node)->token = NULL;
	}
	if (*node)
	{
		free(*node);
		*node = NULL;
	}
}

t_lexer	*delete_redirection_lexer(t_mini *data, t_lexer **node)
{
	t_lexer	*new_next;

	new_next = (*node)->next->next;
	if ((*node)->prev)
		(*node)->prev->next = new_next;
	if (new_next)
		new_next->prev = (*node)->prev;
	if ((*node)->prev == NULL)
		data->lexer = new_next;
	return (new_next);
}

void	add_node_lexer(t_lexer *new_node, t_lexer **token_list)
{
	t_lexer	*temp_node;

	temp_node = *token_list;
	new_node->next = NULL;
	if (*token_list == NULL)
	{
		*token_list = new_node;
		return ;
	}
	while (temp_node->next != NULL)
		temp_node = temp_node->next;
	temp_node->next = new_node;
	new_node->prev = temp_node;
}

t_lexer	*new_node_lexer(char *str, int type)
{
	t_lexer		*new_node;

	new_node = (t_lexer *)malloc(sizeof(t_lexer) * 1);
	if (new_node == NULL)
		return (NULL);
	new_node->token = str;
	new_node->type = type;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
