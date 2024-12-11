/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 13:36:12 by rgiambon          #+#    #+#             */
/*   Updated: 2024/12/10 13:36:29 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

//in this function will be necessary to handle the "Ctrl+C" signal
int	make_heredoc(t_mini *data, t_parser **cmd, char *heredoc_token)
{
	char	*line;
	int	heredoc_fd;

	heredoc_fd = open((*cmd)->heredoc_name, O_CREAT | O_RDWR | O_TRUNC, 0644);
	//handle open error
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, (*cmd)->heredoc_delim) == 0)
		{
			free(line);
			break ;
		}
		if (!is_single_quoted(heredoc_token))
			expand_string(data, &line);
		write(heredoc_fd, line, ft_strlen(line));
		write(heredoc_fd, "\n", 1);
		free(line);
	}
	close(heredoc_fd);
	//check for errors and return failure exit status in case of error
	return (0);
}

char	*new_heredoc_name(void)
{
	static int	hd_num = -1;
	char		*heredoc_name;
	char		*heredoc_num;

	hd_num++;
	heredoc_num = ft_itoa(hd_num);
	//check for malloc fail?
	heredoc_name = ft_strjoin("heredoc_n.", heredoc_num);
	//check for malloc fail?
	free(heredoc_num);
	return (heredoc_name);
}

//add logic if heredoc fails!!!
void	handle_heredoc(t_mini *data, t_parser **cmd, t_lexer **heredoc)
{
	int	marker_count;

	marker_count = 0;
	if ((*cmd)->heredoc_name)
		free((*cmd)->heredoc_name);
	(*cmd)->heredoc_name = new_heredoc_name();
	(*cmd)->heredoc_delim = ft_strdup((*heredoc)->token);
	replace_quotes((*cmd)->heredoc_delim, &marker_count, 0);
	(*cmd)->heredoc_delim = remove_marker((*cmd)->heredoc_delim, marker_count);
	make_heredoc(data, cmd, (*heredoc)->token);
}

void	check_heredoc(t_mini *data, t_parser *cmd)
{
	t_lexer	*redir_tmp;

	(void)data;
	redir_tmp = cmd->redirections;
	while (redir_tmp)
	{
		if (redir_tmp->type == HERE_DOC)
		{
			handle_heredoc(data, &cmd, &redir_tmp);
			 //here we need data to free everything in case of error (?)
			// WHAT HAPPENS IF HEREDOC FAILS????
		}
		redir_tmp = redir_tmp->next;
	}
}
