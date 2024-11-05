/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:35:08 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/05 14:19:19 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

int	is_whitespace(char c)
{
	if (c == ' ' || c > 8 && c < 14)
		return (1);
	return (0);
}

int	read_token(t_mini *data)
{	
	int		i;

	i = 0;
	//remove leading and trailing white spaces:
	data->line = ft_strtrim(input, " ");
	while (data->line[i])
	{
		while (is_whitespace(data->line[i]))
			i++;
		i = i + store_token(&data->line[i], &data->lexer);
	}
}
