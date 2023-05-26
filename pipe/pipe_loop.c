/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:54 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/25 19:39:24 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	first_cmd(t_cmd *cmd, int **fd, int *i, char **env)
{
	char	*s;
	int		pid;

	if (!(*i))
	{
		pipe(fd[*i]);
		pid = fork();
		if (!pid)
		{
			s = builtinnot_path(cmd);
			d_n_c_first(cmd, fd, *i);
			exec_command(cmd, s, env);
			exit(g_data.exit_status);
		}
	}
}

void	last_cmd(t_cmd *cmd, int **fd, int *i, char **env)
{
	char	*s;
	int		pid;

	if (!cmd->next)
	{
		g_data.exit_status = 0;
		if (!cmd->args)
			return ;
		pid = fork();
		if (!pid)
		{
			s = builtinnot_path(cmd);
			d_n_c_last(cmd, fd, *i);
			exec_command(cmd, s, env);
			exit(g_data.exit_status);
		}
	}
}

void	middle_cmd(t_cmd *cmd, int **fd, int *i, char **env)
{
	char	*s;
	int		pid;

	if (cmd->next)
	{
		pipe(fd[++(*i)]);
		close(fd[(*i) - 1][1]);
		pid = fork();
		if (!pid)
		{
			s = builtinnot_path(cmd);
			d_n_c_middle(cmd, fd, *i);
			exec_command(cmd, s, env);
			exit(g_data.exit_status);
		}
	}
}
