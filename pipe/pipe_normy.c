/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_normy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 13:41:09 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/22 11:37:46 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*builtinnot_path(t_cmd *cmd)
{
	char	*s;

	s = NULL;
	if (!is_builtin(cmd))
	{
		s = grant_access(cmd);
		if (!s)
			exit(EXIT_FAILURE);
	}
	return (s);
}

void	d_n_c_first(t_cmd *cmd, int **fd, int i)
{
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	close(fd[i][0]);
	dup2(fd[i][1], cmd->out);
	close(fd[i][1]);
}

void	d_n_c_last(t_cmd *cmd, int **fd, int i)
{
	dup2(cmd->in, 0);
	close(fd[i][1]);
	dup2(fd[i][0], cmd->in);
	dup2(cmd->out, 1);
	close(fd[i][0]);
}

void	d_n_c_middle(t_cmd *cmd, int **fd, int i)
{
	close(fd[i][0]);
	dup2(cmd->in, 0);
	dup2(cmd->out, 1);
	dup2(fd[i - 1][0], cmd->in);
	dup2(fd[i][1], cmd->out);
	close(fd[i][1]);
	close(fd[i - 1][0]);
}

void	exec_command(t_cmd *cmd, char *s, char **envv)
{
	if (cmd->out != -1 && cmd->in != -1)
	{
		if (is_builtin(cmd))
		{
			exec_builtin(cmd);
			exit(1);
		}
		else
		{
			execve(s, cmd->args, envv);
			exit(EXIT_FAILURE);
		}
	}
	else
		exit(0);
}
