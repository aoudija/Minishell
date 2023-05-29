/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 13:23:23 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/29 16:16:36 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fill_env(char **envv)
{
	int	i;

	i = -1;
	while (envv[++i])
		ft_lstadd_back(&g_data.env, ft_lstnew(ft_strdup(envv[i])));
}

void	ft_env(t_cmd *cmd)
{
	t_list	*temp;

	// if (!g_data.env->content)
	// 	return ;
	temp = g_data.env;
	while (temp)
	{
		ft_putstr_fd(temp->content, cmd->out);
		write(cmd->out, "\n", 1);
		temp = temp->next;
	}
	g_data.exit_status = 0;
}
