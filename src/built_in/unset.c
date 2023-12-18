/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:41:18 by afontain          #+#    #+#             */
/*   Updated: 2023/12/18 17:59:11 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tab(char	**tab)
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

void	erase_it(t_mdata *data, char **tab, int nb)
{
	char	**newtab;
	int		len;
	int		i;
	int		j;

	len = 0;
	i = 0;
	while (tab[len])
		len++;
	newtab = malloc(sizeof(char *) * len);
	if (!newtab)
		exit_mini(data);
	while (j < len)
	{
		if (i != nb)
			newtab[i++] = ft_strdup(tab[j]);
		j++;
	}
	newtab[i] = NULL;
	free_tab(tab);
	tab = newtab;
}

int	line_exist(char **tab, char *line)
{
	int	len = ft_strlen(line);
	int	i;

	i = 0;
	while (tab[i])
	{
		if (ft_strncmp(tab[i], line, len) == 0)
		{
			if (tab[i][len] == '=')
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
	
	line_env = line_exist(data->env, str);
	line_export = line_exist(data->env, str);
	if (line_env >= 0)
		erase_it(data, data->env, line_env);
	else if (line_export >= 0)
		erase_it(data, data->export, line_export);
	return ;
}

int	ft_unset(char **args, t_mdata *data)
{
	int		i;

	i = 0;
	if (!args || !args[0])
		return (0);
	while (args[i])
	{
		unset_utils(data, args[i]);
		i++;
	}
	return (0);
}
