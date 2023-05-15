/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoudija <aoudija@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 15:05:55 by aoudija           #+#    #+#             */
/*   Updated: 2023/05/05 17:30:21 by aoudija          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(char *str, char *st)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != st[i])
			break ;
	}
	return (str[i] - st[i]);
}
