/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 17:46:08 by afontain          #+#    #+#             */
/*   Updated: 2024/02/20 20:25:58 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*find_in_tab(t_mdata *data, char *var, int len, char **tab)
{	
	int		k;
	char	*value;

	(void)data;
	k = 0;
	if (!tab)
		return (NULL);
	while (tab[k] && ft_strncmp((const char *)var, tab[k], len) != 0)
		k++;
	if (!tab[k])
		return (NULL);
	if (tab[k][len] != '=' || (tab[k][len] == '=' && tab[k][len + 1] == '\0'))
		return (NULL);
	else
		value = ft_strdup(&tab[k][len + 1]);
	return (value);
}

char	*find_goodpart(t_mdata *data, t_command *cmd, int i)
{	
	int		j;
	char	*str1;

	j = i;
	while (ft_isalnum(cmd->line[i + 1]) == 1)
		i++;
	str1 = ft_strdupfromuntil(data, cmd->line, j + 1, (i - j));
	return (str1);
}

char	*find_var(t_mdata *data, t_command *cmd, int i)
{
	int		len;
	char	*var;
	char	*str1;

	var = find_goodpart(data, cmd, i);
	len = ft_strlen(var);
	str1 = find_in_tab(data, var, len, data->env);
	if (!str1)
		str1 = find_in_tab(data, var, len, data->export);
	if (!str1)
		del_vdollar(data, cmd, i, len);
	else
		change_letter(data, cmd, i, str1);
	ft_free_me(var);
	return (str1);
}

int	handle_letter(t_mdata *data, t_command *cmd, int i)
{
	char	*value;
	char	*start;

	start = ft_strdupuntil(data, cmd->line, i);
	value = find_var(data, cmd, i);
	if (!start)
		ft_error(data, "Error: malloc\n", -1);
	i = ft_strlen(start) + ft_strlen(value);
	ft_free_me(value);
	ft_free_me(start);
	return (i - 1);
}
