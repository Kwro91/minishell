/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ?.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:45:04 by afontain          #+#    #+#             */
/*   Updated: 2024/02/15 17:44:40 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *replace_retval(t_command *cmd, int i)
{
	char *retu;
	char *resu;
	char *avant;
	char *apres;
	char	*new;
	
	retu = ft_itoa(g_retval);
	avant = ft_strdupuntil(cmd->line, i - 1);
	resu = ft_strjoin(avant, retu);
	free(avant);
	// apres = ft_strdupfrom(resu, i + ft_strlen(retu));
	apres = ft_strdup(&cmd->line[i + 2]);
	new = ft_strjoin(resu, apres);
	free(retu);
	free(resu);
	free(apres);
	// if (new)
	// 	ft_printf("newline:%s\n", new);
	cmd->line = new;
	return (i + ft_strlen(retu));
}