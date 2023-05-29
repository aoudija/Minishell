/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   empty.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 14:56:29 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/29 17:57:28 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	both_empty(t_cmd *cmd, int i)
{
	if (!g_data.exp && !g_data.env)
	{
		g_data.exp = NULL;
		g_data.env = NULL;
		ft_lstadd_back(&g_data.exp, ft_lstnew(ft_strjoin("declare -x ", cmd->args[i])));
		if (ft_strchr(cmd->args[i], '='))
			ft_lstadd_back(&g_data.env, ft_lstnew(ft_strdup(cmd->args[i])));
		return (1);
	}
	return (0);
}

int	exp_empty(t_cmd *cmd, int i, int plus)
{
	if (!g_data.exp && g_data.env)
	{
		g_data.exp = NULL;
		ft_lstadd_back(&g_data.exp, ft_lstnew(ft_strjoin("declare -x ", cmd->args[i])));
		if (ft_strchr(cmd->args[i], '='))
		{
			if(env_new(cmd, i, plus))
				ft_lstadd_back(&g_data.env,
					ft_lstnew(ft_strdup(cmd->args[i])));
		}
		return (1);
	}
	return (0);
}

int	check(t_cmd *cmd, int i)
{
	int	plus;

	plus = 0;
	if (ft_strchr(cmd->args[i], '+'))
	{
		cmd->args[i] = remove_char(cmd->args[i], '+');
		plus = 1;
	}
	if (both_empty(cmd, i))
		return (1);
	if (exp_empty(cmd, i, plus))
		return (1);
	if (g_data.exp && !g_data.env)
	{
		if (!ft_strchr(cmd->args[i], '='))
			export_norm2(cmd, i);
		else if (ft_strchr(cmd->args[i], '='))
		{
			if (!exp_matching_vars(cmd, i, plus))
				ft_lstadd_back(&g_data.exp,
					ft_lstnew(exp_new_content(cmd->args[i])));
		}
		g_data.env = NULL;
		if (ft_strchr(cmd->args[i], '='))
			ft_lstadd_back(&g_data.env, ft_lstnew(ft_strdup(cmd->args[i])));
		return (1);
	}
	return (0);
}
