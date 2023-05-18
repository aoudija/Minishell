/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grant_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 12:54:22 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/17 15:07:21 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*grant_access(t_cmd *cmd)
{
	char	*s;
	char	*err;

	if (!ft_strchr(cmd->args[0], '/'))
		s = cmd_path(cmd);
	else
		s = ft_strdup(cmd->args[0]);
	if (access(s, F_OK | X_OK) == -1)
	{
		if (errno == 14)/*bad adress*/
		{
			err = ft_strjoin("bashn't: ", cmd->args[0]);
			err = ft_strjoin_frees1(err, ": command not found");
			printf("%s\n", err);
			free(err);
			return (NULL);
		}
		else
		{
			err = ft_strjoin("bashn't: ", cmd->args[0]);
			perror(err);
			free(err);
			free(s);
			return (NULL);
		}
	}
	return (s);
}
