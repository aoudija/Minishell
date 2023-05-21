/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 16:13:14 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/20 12:57:06 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pipe_it(t_cmd *cmd, char **envv)
{
	int		**fd;
	int		i;
	t_cmd	*tmp;

	tmp = cmd;
	fd = malloc(sizeof(int *) * (cmd_list_size(cmd) - 1));
	i = cmd_list_size(cmd) - 2;
	while (i >= 0)
	{
		fd[i] = malloc(sizeof(int) * 2);
		i--;
	}
	i = 0;
	while (cmd->next)
	{
		first_cmd(cmd, fd, &i, envv);
		cmd = cmd->next;
		last_cmd(cmd, fd, &i, envv);
		middle_cmd(cmd, fd, &i, envv);
	}
	close_fdeez(tmp, fd);
}

void	fork_n_exec(t_cmd *cmd, char *s, char **envv)
{
	int	pid;

	pid = fork();
	if (!pid)
	{
		dup2(cmd->in, 0);
		dup2(cmd->out, 1);
		execve(s, cmd->args, envv);
		free(s);
		perror("");
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid, &g_data.exit_status, 0);
		printf("->%d\n", g_data.exit_status);
		free(s);
		ft_free(envv);
		return ;
	}
}

void	execute_it(t_cmd *cmd)
{
	char	*s;
	char	**envv;

	envv = put_in_tab();
	if (!cmd->next)
	{
		if (cmd->in == -1 || cmd->out == -1)
			return ;
		if (!cmd->args)
			return ;
		s = grant_access(cmd);
		if (!s)
			return ;
		fork_n_exec(cmd, s, envv);
		return ;
	}
	pipe_it(cmd, envv);
	ft_free(envv);
}
