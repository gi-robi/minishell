/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgiambon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 10:11:59 by rgiambon          #+#    #+#             */
/*   Updated: 2024/11/27 16:02:48 by rgiambon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/mini.h"

void	execute_command(t_mini *data, t_parser *cmd)
{
	char	*path;
	char	**env;

	if (cmd->redirections && redirections(cmd) != EXIT_SUCCESS)
		exit (EXIT_FAILURE);
	if (cmd->builtin)
		exit (call_builtin_function(data, cmd));
	env = env_list_to_strarr(data);
	path = path_finder(cmd->commands[0], env);
	if (path == NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd->commands[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		exit (127);
	}
	execve(path, cmd->commands, env);
	free_strarr(env);
//considering protecting the execve
	exit (EXIT_SUCCESS);
}

void	one_command(t_mini *data)
{
	int	child_status;
	int	pid;
	t_parser	*cmd;

	cmd = data->parser;
	if (cmd->builtin && builtin_in_parent(cmd->commands[0]))
	{
		data->exit_code = call_builtin_function(data, cmd);	
		return ;
	}
	check_heredoc(data, data->parser);
	pid = fork();
	if (pid < 0)
		free_data_and_exit(data, 1);
	if (pid == 0)
		execute_command(data, data->parser);
	waitpid(pid, &child_status, 0);
	if (WIFEXITED(child_status))
		data->exit_code = WEXITSTATUS(child_status);
}

void	executor(t_mini *data)
{
	int		commands;

//	signal(SIGQUIT, handle_sigquit); option
// 	signal(SIGQUIT, SIG_IGN); ---- Ignore SIGQUIT (Ctrl+\)
//	data->in_cmd = 1;
	commands = count_nodes(data->parser);
	if (commands > 1)
	{
		data->pids = (int *)malloc(sizeof(int) * commands);
		if (data->pids == NULL)
			free_data_and_exit(data, 1);
		multiple_commands(data);
	}
	else
		one_command(data);
//	data->in_cmd = 0;
}
