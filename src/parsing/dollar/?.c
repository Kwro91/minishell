/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ?.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:45:04 by afontain          #+#    #+#             */
/*   Updated: 2024/02/16 17:59:19 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	replace_retval(t_mdata *data, t_command *cmd, int i)
{
	char *retu;
	char *resu;
	char *avant;
	char *apres;
	char	*new;
	
	retu = ft_itoa(g_retval);
	avant = ft_strdupuntil(data, cmd->line, i);
	resu = ft_strjoin(avant, retu);
	ft_free_me(avant);
	apres = ft_strdup(&cmd->line[i + 2]);
	new = ft_strjoin(resu, apres);
	i += ft_strlen(retu);
	ft_free_me(retu);
	ft_free_me(resu);
	ft_free_me(apres);
	ft_free_me(cmd->line);
	cmd->line = new;
	return (i - 1);
}
