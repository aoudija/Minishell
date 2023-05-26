/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 23:52:49 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/24 20:04:17 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	execute(t_cmd	*cmd)
{
	if (!cmd || (!cmd->args && !cmd->next))
		return ;
	if (cmd_list_size(cmd) == 1 && is_builtin(cmd))
	{
		if (!ft_strcmp("echo", cmd->args[0]) && !cmd->next
			&& cmd->error)
			ft_echo(cmd);
		else if (!ft_strcmp("env", cmd->args[0]) && !cmd->next)
			ft_env(cmd);
		else if (!ft_strcmp("exit", cmd->args[0]) && !cmd->next)
			ft_exit(cmd);
		else if (!ft_strcmp("export", cmd->args[0]) && !cmd->next)
			ft_export(cmd);
		else if (!ft_strcmp("unset", cmd->args[0]) && !cmd->next)
			ft_unset(cmd);
		else if (!ft_strcmp("cd", cmd->args[0]) && !cmd->next)
			cd(cmd);
		else if (!ft_strcmp("pwd", cmd->args[0]) && !cmd->next)
			pwd(cmd);
	}
	else
		execute_it(cmd);
}
