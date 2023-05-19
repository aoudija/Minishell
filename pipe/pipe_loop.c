/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:47:54 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/19 20:50:48 by aoudija          ###   ########.fr       */
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
			dup2(cmd->in, 0);
			dup2(cmd->out, 1);
			close(fd[*i][0]);
			dup2(fd[*i][1], cmd->out);
			close(fd[*i][1]);
			// d_n_c_first(cmd, fd, *i);
			exec_command(cmd, s, env);
		}
	}
}

void	last_cmd(t_cmd *cmd, int **fd, int *i, char **env)
{
	char	*s;
	int		pid;

	if (!cmd->next)
	{
		
		if (!cmd->args)
			return ;
		pid = fork();
		if (!pid)
		{
			s = builtinnot_path(cmd);
			dup2(cmd->in, 0);
			close(fd[*i][1]);
			dup2(fd[*i][0], cmd->in);
			dup2(cmd->out, 1);
			close(fd[*i][0]);
			// d_n_c_last(cmd, fd, *i);
			exec_command(cmd, s, env);
			exit(EXIT_FAILURE);
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
		pid = fork();
		close(fd[(*i) - 1][1]);
		if (!pid)
		{
			s = builtinnot_path(cmd);
			d_n_c_middle(cmd, fd, *i);
			exec_command(cmd, s, env);
		}
		close(fd[(*i) - 1][0]);
	}
}
