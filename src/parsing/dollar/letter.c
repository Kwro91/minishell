/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:08 by afontain          #+#    #+#             */
/*   Updated: 2024/02/16 17:20:16 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// $x
//si x est une lettre on vient ici, on cherche dans l'env et export x, si x existe on remplace $x par var
//si x n'existe pas ou si la var n'existe pas, on supprime $x ("")
char	*find_in_tab(t_mdata *data, char *var, int len, char **tab)
{	
	int 	k;
	char	*value;

	k = 0;
	while (ft_strncmp((const char *)var, tab[k], len) != 0 && tab)
		k++;
	if (!tab[k])
		return (NULL);
	if (tab[k][len+1] != '=' || (tab[k][len+1] == '=' && tab[k][len+2] == '\0'))
		return (NULL);
	else
		value = ft_strdupfrom(data, tab[k], len+2);
	return (value);
}

char	*find_goodpart(t_mdata *data, t_command *cmd, int i)
{	
	int j;
	char *str1;
	
	j = i;
	while (ft_isalnum(cmd->line[i+1]) == 1)
		i++;
	str1 = ft_strdupfromuntil(data, cmd->line, j+1, i - j);
	return (str1);
}

char	*find_var(t_mdata *data, t_command *cmd, int i)
{
	int len;
	char *var;
	char *str1;

	var = find_goodpart(data, cmd, i);
	len = ft_strlen(var);
	i = 0;
	str1 = find_in_tab(data, var, len, data->env);
	if (!str1)
		str1 = find_in_tab(data, var, len, data->export);
	return (str1);
}

int	handle_letter(t_mdata *data, t_command *cmd, int i)
{
	char	*value;
	char	*start;
	char	*end;
	char	*tmp;
	
	value = find_var(data, cmd, i);
	printf("value : %s\n", value);
	start = ft_strdupuntil(data, cmd->line, i);
	// if (!start || !end)
	// ft_free_me(cmd->line);
	if (!value)
	{
		tmp = find_goodpart(data, cmd, i);
		end = ft_strdupfrom(data, cmd->line, i + ft_strlen(tmp));
		cmd->line = ft_strjoin(start, end);
	}
	else
	{
		tmp = ft_strjoin(start, value);
		end = ft_strdupfrom(data, cmd->line, i + ft_strlen(tmp));
		cmd->line = ft_strjoin(tmp, end);
	}
	i = ft_strlen(start) + ft_strlen(value); //a verifier
	// ft_free_me(tmp);
	// ft_free_me(start);
	// ft_free_me(end);
	return (i);
}
