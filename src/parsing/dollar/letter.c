/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:08 by afontain          #+#    #+#             */
/*   Updated: 2024/02/16 19:33:34 by besalort         ###   ########.fr       */
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

	(void)data;
	k = 0;
	if (!tab)
		return (NULL);
	while (ft_strncmp((const char *)var, tab[k], len) != 0 && tab)
		k++;
	if (!tab[k])
		return (NULL);
	if (tab[k][len] != '=' || (tab[k][len] == '=' && tab[k][len + 1] == '\0'))
		return (NULL);
	else
		value = ft_strdup(&tab[k][len+1]);
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

void	change_letter(t_mdata *data, t_command *cmd, int i, char *value, int len)
{
	char	*tmp;
	char	*start;
	char	*end;

	start = ft_strdupuntil(data, cmd->line, i);
	tmp = ft_strjoin(start, value);
	end = ft_strdup(&cmd->line[i + len]);
	if (end)
		cmd->line = ft_strjoin(tmp, end);
	else
		cmd->line = tmp;
	ft_free_me(start);
	ft_free_me(end);
	ft_free_me(tmp);
	if (!cmd->line)
		ft_error(data, "Error: malloc\n", 1);
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
	if (!str1)
		del_vdollar(data, cmd, i, len);
	else
		change_letter(data, cmd, i, str1, len);
	return (str1);
}

int	handle_letter(t_mdata *data, t_command *cmd, int i)
{
	char	*value;
	char	*start;
	
	value = find_var(data, cmd, i);
	start = ft_strdupuntil(data, cmd->line, i);
	if (!start)
		ft_error(data, "Error: malloc\n", 1);
	i = ft_strlen(start) + ft_strlen(value); //a verifier
	ft_free_me(value);
	ft_free_me(start);
	return (i - 1);
}
