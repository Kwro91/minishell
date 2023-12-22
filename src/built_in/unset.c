/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:41:18 by afontain          #+#    #+#             */
/*   Updated: 2023/12/22 17:35:56 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**erase_it(t_mdata *data, char **tab, int nb)
{
	char	**newtab;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	j = 0;
	while (tab[len])
		len++;
	newtab = malloc(sizeof(char *) * len);
	if (!newtab)
		exit_mini(data);
	while (tab[j])
	{
		if (j != nb)
			newtab[i++] = ft_strdup(tab[j]);
		j++;
	}
	newtab[i] = NULL;
	return (newtab);
}

int	line_exist(char **tab, char *line)
{
	int	lenl;
	int	lenm;
	int	i;

	i = 0;
	lenl = ft_strlen(line);
	if (!tab)
		return (-1);
	while (tab && tab[i])
	{
		lenm = lenl;
		if (ft_strncmp(tab[i], line, lenm - 1) == 0)
		{
			if (tab[i][lenm] == '=' || tab[i][lenm] == '\0')
				return (i);
		}
		i++;
	}
	return (-1);
}

void	unset_utils(t_mdata *data, char *str)
{
	int	line_env;
	int	line_export;
	char	**newtab;
	
	line_env = line_exist(data->env, str);
	line_export = line_exist(data->export, str);
	if (line_env >= 0)
	{
		newtab = erase_it(data, data->env, line_env);
		free_tab(data->env);
		data->env = newtab;
	}
	else if (line_export >= 0)
	{
		newtab = erase_it(data, data->export, line_export);
		free_tab(data->export);
		data->export = newtab;
	}
	return ;
}

int	ft_unset(char **args, t_mdata *data)
{
	int		i;

	i = 1;
	if (!args || !args[0])
		return (0);
	while (args[i])
	{
		unset_utils(data, args[i]);
		i++;
	}
	return (0);
}
