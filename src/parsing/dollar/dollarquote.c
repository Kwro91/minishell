/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollarquote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:50:04 by afontain          #+#    #+#             */
/*   Updated: 2024/02/16 19:21:23 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//dans ce cas on ne supprime QUE le $

char	*del_qdollar(t_mdata *data, t_command *cmd, int i)
{
	char	*str2;
	char	*str1;
	int		j;

	j = i;
	i++;
	str1 = ft_strdupuntil(data, cmd->line, j - 1);
	str2 = ft_strdup(&cmd->line[i]);
	cmd->line = ft_strjoin(str1, str2);
	return (cmd->line);
}