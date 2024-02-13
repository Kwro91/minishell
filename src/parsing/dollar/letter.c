/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:08 by afontain          #+#    #+#             */
/*   Updated: 2024/02/13 17:55:29 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// $x
//si x est une lettre on vient ici, on cherche dans l'env et export x, si x existe on remplace $x par var
//si x n'existe pas ou si la var n'existe pas, on supprime $x ("")

int	find_var(t_mdata *data, char *cmd)
{
	int	i;

	i = 0;
	while (ft_strncmp((const char *)cmd->line, data->env[i], ft_strlen(cmd)) != 0)
	{
		i++;
		if (i == nb_word(data->env))
			return (cmd->line);
			return (ft_printf("\n"));
	}
	
}