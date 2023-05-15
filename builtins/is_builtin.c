/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 08:34:02 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/15 08:37:30 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int is_builtin(t_cmd *cmd)
{
    if (!ft_strcmp("echo", cmd->cmd))
		return (1);
	else if (!ft_strcmp("env", cmd->cmd))
		return (1);
	else if (!ft_strcmp("export", cmd->cmd))
		return (1);
	else if (!ft_strcmp("unset", cmd->cmd))
		return (1);
	else if (!ft_strcmp("cd", cmd->cmd))
		return (1);
	else if (!ft_strcmp("pwd", cmd->cmd))
		return (1);
    return (0);
}