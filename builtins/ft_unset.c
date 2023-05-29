/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 13:35:11 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/29 18:21:20 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	shut_up_norma(t_list **tenv, t_list **temp)
{
	if ((*tenv)->next)
	{
		free((*tenv)->content);
		(*tenv)->content = (*tenv)->next->content;
		free((*tenv)->next);
		(*tenv)->next = (*tenv)->next->next;
	}
	else if (!(*tenv)->next)
	{
		if (ft_lstsize((*tenv)) == 1)
		{
			free((*tenv)->content);
			free((*tenv));
			(*tenv)->content = NULL;
			(*tenv) = NULL;
			return ;
		}
		while ((*temp)->next->next)
			(*temp) = (*temp)->next;
		free((*temp)->next->content);
		free((*temp)->next);
		(*temp)->next->content = NULL;
		(*temp)->next = NULL;
	}
}

void	lenv(char	*arg)
{
	t_list	*tenv;
	t_list	*temp;
	char	*t;

	temp = g_data.env;
	tenv = g_data.env;
	if (!tenv->content)
		return ;
	printf("hey\n");
	while (tenv)
	{
		t = ft_substr(tenv->content, 0, strlen_var(tenv->content));
		if (!ft_strcmp(t, arg))
			shut_up_norma(&tenv, &temp);
		free(t);
		if (tenv)
			tenv = tenv->next;
		else
			tenv = NULL;
	}
}

void	lexp(char *arg)
{
	t_list	*texp;
	t_list	*temp;
	char	*t;

	if (!g_data.exp->content)
		return ;
	texp = g_data.exp;
	temp = g_data.exp;
	while (texp)
	{
		t = ft_substr(texp->content + 11, 0, strlen_var(texp->content + 11));
		if (!ft_strcmp(t, arg))
			shut_up_norma(&texp, &temp);
		free(t);
		if (texp)
			texp = texp->next;
		else
			texp = NULL;
	}
}

void	ft_unset(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
		return ;
	while (cmd->args[++i])
	{
		if (var_is_valid(cmd, cmd->args[i]))
		{
			lenv(cmd->args[i]);
			lexp(cmd->args[i]);
		}
	}
}
