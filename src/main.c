/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:35:19 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/10 12:44:37 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/strarr_utils.h"
#include <stdlib.h>

void	init_data(t_mini *data, char **env)
{
	data->line = NULL;
	data->envp = strarr_copy(env);
	if (data->envp == NULL)
		exit(EXIT_FAILURE);
	data->lexer = NULL;
	data->parser = NULL;
}

int	main(int argc, char **argv, char **env)
{
	t_mini		data;
	
	if (argc != 1)
	{
		printf("No arguments accepted.\n");
		return (EXIT_SUCCESS);
	}
	init_data(&data, env);
	//someone is adding a welcome message, maybe we should do the same (?)
	mini_loop(&data);
	
	return (EXIT_SUCCESS);
}
	
	
