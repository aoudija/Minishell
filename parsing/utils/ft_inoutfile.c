/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_inoutfile.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 21:17:18 by abelhadj          #+#    #+#             */
/*   Updated: 2023/05/22 17:04:09 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../../include/minishell.h"

void	ft_get_infile(t_cmd **cmd, char *value, t_token *tmp)
{
	if (!ft_strcmp(value, "\b"))
	{
		ft_putstr_fd("bashn't: ambiguous redirect\n", 2);
		(*cmd)->in = -1;
		(*cmd)->error = 0;
		tmp->err = 1;
	}
	if ((*cmd)->in != -1)
	{
		(*cmd)->in = open(value, O_RDONLY);
		if ((*cmd)->in == -1)
		{
			ft_putstr_fd("bashn't: ", 2);
			perror(value);
			(*cmd)->error = 0;
			tmp->err = 1;
		}
	}
}

void	ft_get_outfile(t_cmd **cmd, char *value, t_token *tmp)
{
	if (!ft_strcmp(value, "\b"))
	{
		ft_putstr_fd("bashn't: ambiguous redirect\n", 2);
		(*cmd)->out = -1;
		(*cmd)->error = 0;
		tmp->err = 1;
	}
	if ((*cmd)->out != -1)
	{
		(*cmd)->out = open(value, O_CREAT | O_TRUNC | O_RDWR, 0777);
		if ((*cmd)->out == -1)
		{
			ft_putstr_fd("bashn't: ", 2);
			perror(value);
			(*cmd)->error = 0;
			tmp->err = 1;
		}
	}
}

void	ft_get_append(t_cmd **cmd, char *value, t_token *tmp)
{
	if (!ft_strcmp(value, "\b"))
	{
		ft_putstr_fd("bashn't: ambiguous redirect\n", 2);
		(*cmd)->out = -1;
		(*cmd)->error = 0;
		tmp->err = 1;
	}
	if ((*cmd)->out != -1)
	{
		(*cmd)->out = open(value, O_CREAT | O_APPEND | O_RDWR, 0777);
		if ((*cmd)->out == -1)
		{
			ft_putstr_fd("bashn't: ", 2);
			perror(value);
			(*cmd)->error = 0;
			tmp->err = 1;
		}
	}
}

int	ft_stop(t_token *data)
{
	t_token	*tmp;

	tmp = data;
	while (tmp->prev && tmp->type != PIPE)
	{
		if (tmp->err == 1)
			return (0);
		tmp = tmp->prev;
	}
	return (1);
}

void	ft_inoutfile(t_token *tmp, t_cmd **cmd)
{
	if (tmp->type == INFILE && ft_stop(tmp))
		ft_get_infile(cmd, tmp->value, tmp);
	else if (tmp->type == OUTFILE && ft_stop(tmp))
		ft_get_outfile(cmd, tmp->value, tmp);
	else if (tmp->type == APPEND && ft_stop(tmp))
		ft_get_append(cmd, tmp->next->value, tmp);
	else if (tmp->type == HERDOC && ft_stop(tmp))
		ft_get_infile(cmd, tmp->next->value, tmp);
}