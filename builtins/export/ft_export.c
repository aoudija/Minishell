/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 10:47:48 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/18 12:52:33 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*exp_new_content(char *arg)
{
	char	*t;
	char	*d;
	char	*sub;

	d = ft_strdup("declare -x ");
	sub = ft_substr(arg, 0, strlen_var(arg) + 1);
	t = ft_strjoin(d, sub);
	free(sub);
	free(d);
	d = ft_strjoin(t, "\"");
	free(t);
	t = ft_strjoin(d, arg + (strlen_var(arg) + 1));
	free(d);
	d = ft_strjoin(t, "\"");
	free(t);
	return (d);
}

int	exp_matching_vars(t_cmd *cmd, int i, int plus)
{
	t_list	*temp_exp;
	int		c;

	c = 0;
	temp_exp = g_data.exp;
	while (temp_exp)
	{
		if (ft_strchr(temp_exp->content, '=')
			&& !var_compare(temp_exp->content + 11, cmd->args[i]))
		{/*join*/
			if (plus)
				temp_exp->content = exp_plus(temp_exp->content, cmd->args[i]);
			else
				temp_exp->content = exp_new_content(cmd->args[i]);
			c = 1;
		}
		else if (!ft_strchr(temp_exp->content, '=')
			&& !ft_strcmp(temp_exp->content + 11,
				ft_substr(cmd->args[i], 0, strlen_var(cmd->args[i]))))
		{
			temp_exp->content = exp_new_content(cmd->args[i]);
			c = 1;
		}
		temp_exp = temp_exp->next;
	}
	return (c);
}

int	env_new(t_cmd *cmd, int i, int plus)
{
	t_list	*temp_env;

	temp_env = g_data.env;
	while (temp_env)
	{
		if (ft_strchr(temp_env->content, '=')
			&& !var_compare(temp_env->content, cmd->args[i]))
		{/*join*/
			if (plus)
				temp_env->content = env_plus(temp_env->content, cmd->args[i]);
			else
				temp_env->content = ft_strdup(cmd->args[i]);
			return (0);
		}
		temp_env = temp_env->next;
	}
	return (1);
}

void	ft_export(t_cmd *cmd)
{
	t_list	*temp_exp;
	int		i;

	i = 0;
	temp_exp = g_data.exp;
	if (!cmd->args[1])
	{
		while (temp_exp)
		{
			ft_putstr_fd(temp_exp->content, cmd->out);
			write(cmd->out, "\n", 1);
			temp_exp = temp_exp->next;
		}
		return ;
	}
	while (cmd->args[++i])
	{
		if (var_is_valid(cmd, cmd->args[i]))
		{
			if (ft_strchr(cmd->args[i], '='))
				export_norm1(cmd, i);
			else if (!ft_strchr(cmd->args[i], '='))
				export_norm2(cmd, i);
		}
	}
	sort_exp();
}
