/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:08 by afontain          #+#    #+#             */
/*   Updated: 2024/02/15 18:27:48 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// $x
//si x est une lettre on vient ici, on cherche dans l'env et export x, si x existe on remplace $x par var
//si x n'existe pas ou si la var n'existe pas, on supprime $x ("")

char *find_goodpart(t_command *cmd, int i)
{	
	int j;
	char *str1;
	
	j = i;
	while (ft_isalnum(cmd->line[i+1]) == 1)
		i++;
	str1 = ft_strdupfromuntil(cmd->line, j+1, i - j);
	return (str1);
}

char	*find_var(t_mdata *data, t_command *cmd, int i)
{
	int j;
	int k;
	int r;
	char *new;
	char *str1;

	k = 0;
	new = find_goodpart(cmd->line, i);
	j = ft_strlen(new);
	i = 0;
	while (ft_strncmp((const char *)new, data->env[i], ft_strlen(new)) != 0 && data->envi)
		i++;
	if (data->env[i] == '\0')
	{
		while (ft_strncmp((const char *)new, data->export[k], ft_strlen(new)) != 0 && data->export)
			k++;
		if (data->export[k][j+1] != '=' || (data->export[k][j+1] =='=' && data->export[k][j+2] == '\0'))
			return (cmd = ' ');
		else if (data->export[k][j+1] == '=' && data->export[k][j+2] != '\0')
			new = ft_strdupfrom(data->export[k], j+2);
		
	}
	if (data->env[i][j+1] == '=')
	{
		//meme chose que le cas du dessus
	}
	cmd->line = ft_strjoin(avant, new, apres);
	return (new);
}