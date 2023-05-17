/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:52:49 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/15 18:54:41 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute(t_cmd	*cmd)
{
	if (!cmd->cmd)
		return ;
	if (!ft_strcmp("echo", cmd->cmd) && !cmd->next)
		ft_echo(cmd);
	else if (!ft_strcmp("env", cmd->cmd) && !cmd->next)
		ft_env(cmd);
	else if (!ft_strcmp("export", cmd->cmd) && !cmd->next)
		ft_export(cmd);
	else if (!ft_strcmp("unset", cmd->cmd) && !cmd->next)
		ft_unset(cmd);
	else if (!ft_strcmp("cd", cmd->cmd) && !cmd->next)
		cd(cmd);
	else if (!ft_strcmp("pwd", cmd->cmd) && !cmd->next)
	{
		printf("hey\n");
		pwd(cmd);
	}
	else
		execute_it(cmd);
}
