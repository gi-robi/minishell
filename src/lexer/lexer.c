/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:35:08 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/27 15:56:07 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"
#include <stdio.h>

void	read_token(t_mini *data)
{	
	int		i;
	int		j;
	char		*line;
	i = 0;

	line = ft_strtrim(data->line, " ");
	free(data->line);
//	data->line = remove_quotes(line);
	data->line = line;
	while (data->line[i])
	{
		while (is_whitespace(data->line[i]))
			i++;
		j = store_token(&data->line[i], data);
		if (j < 0)
			free_data_and_exit(data, EXIT_FAILURE);
		i = i + j;
	}
//	remove_inside_quotes(data);
}
