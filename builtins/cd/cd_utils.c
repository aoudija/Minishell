/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 21:12:55 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/30 15:31:08 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_env(char *str, char *new)
{
	t_list	*temp;
	char	*sub;
	char	*s;

	temp = g_data.env;
	while (temp)
	{
		sub = ft_substr(temp->content, 0, ft_strlen(str));
		if (!ft_strcmp(sub, str))
		{
			s = ft_strjoin(str, "=");
			s = ft_strjoin_frees1(s, new);
			free(temp->content);
			temp->content = s;
		}
		free(sub);
		temp = temp->next;
	}
}

void	change_exp(char *str, char *new)
{
	t_list	*temp;
	char	*sub;
	char	*s;

	temp = g_data.exp;
	while (temp)
	{
		sub = ft_substr(temp->content + 11, 0, ft_strlen(str));
		if (!ft_strcmp(sub, str))
		{
			s = ft_strjoin(str, "=");
			s = ft_strjoin_frees1(s, new);
			free(temp->content);
			temp->content = exp_new_content(s);
			free(s);
		}
		free(sub);
		temp = temp->next;
	}
}

void	norma_cd_1(t_cmd *cmd, char *cwd, int i)
{
	char	*err;
	char	new[PATH_MAX];

	if (i == -1)
	{
		err = ft_strjoin("bashn't: ", cmd->args[0]);
		err = ft_strjoin_frees1(err, ": ");
		err = ft_strjoin_frees1(err, cmd->args[1]);
		perror(err);
		free(err);
		g_data.exit_status = 1;
	}
	else if (!i)
	{
		search_var("OLDPWD", cwd);
		getcwd(new, sizeof(new));
		search_var("PWD", new);
		g_data.exit_status = 0;
	}
}

void	norma_cd_2(char *cwd)
{
	char	*err;
	char	new[PATH_MAX];

	if (found_var("HOME"))
	{
		chdir(found_var("HOME"));
		search_var("OLDPWD", cwd);
		getcwd(new, sizeof(new));
		search_var("PWD", new);
		g_data.exit_status = 0;
	}
	else
	{
		err = ft_strdup("bashn't: cd: HOME not set\n");
		ft_putstr_fd(err, 2);
		free(err);
		g_data.exit_status = 127;
	}
}
