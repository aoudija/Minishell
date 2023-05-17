/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/13 16:52:50 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/16 17:23:01 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	export_norm1(t_cmd *cmd, int i)
{
	int	c;
	int	plus;
/*remove plus from here and add an integer 
indexing"plus was here" than passit to other fellas*/
	plus = 0;
	if (ft_strchr(cmd->args[i], '+'))
	{
		cmd->args[i] = remove_char(cmd->args[i], '+');
		plus = 1;
	}
	printf("@@%s\n", cmd->args[i]);
	c = 0;
	c = exp_matching_vars(cmd, i);
	if (env_new_exp(cmd, i, c))
	{
		ft_lstadd_back(&g_data.env, ft_lstnew(ft_strdup(cmd->args[i])));
		if (!c)
			ft_lstadd_back(&g_data.exp,
				ft_lstnew(exp_new_content(cmd->args[i])));
	}
}

void	export_norm2(t_cmd *cmd, int i)
{
	t_list	*temp_exp;
	int		next;
	char	*t;

	next = 1;
	temp_exp = g_data.exp;
	while (temp_exp)
	{
		t = ft_substr(temp_exp->content + 11, 0,
				strlen_var(temp_exp->content + 11));
		if (next && !ft_strcmp(t, cmd->args[i]))
			next = 0;
		temp_exp = temp_exp->next;
		free(t);
	}
	if (next)
		ft_lstadd_back(&g_data.exp,
			ft_lstnew(ft_strjoin("declare -x ", cmd->args[i])));
}

char	*remove_char(char *str,char c)
{
	int		i;

	i = -1;
	while (str[++i] != '=')
	{
		if (str[i] == c)
		{
			while (str[i + 1])
			{
				str[i] = str[i + 1];
				i++;
			}
			str[i] = 0;
		}
	}
	return (str);
}
