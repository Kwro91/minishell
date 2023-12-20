/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:41:18 by afontain          #+#    #+#             */
/*   Updated: 2023/12/20 15:51:36 by besalort         ###   ########.fr       */
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
	j = 0;
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
	int	lenl;
	int	lent;
	int	i;

	i = 0;
	lenl = ft_strlen(line);
	if (!tab)
		return (-1);
	printf("%s est la premiere ligne de tab\n", tab[0]);
	while (tab && tab[i])
	{
		lent = ft_strlen(tab[i]);
		if (lenl <= lent)
		{
			if (ft_strncmp(tab[i], line, lenl - 1) == 0)
			{
				if (tab[i][lenl] == '=')
					return (i);
			}
		}
		else
		{
			if (ft_strncmp(tab[i], line, lent - 1) == 0)
			{
				if (tab[i][lent] == '=')
					return (i);
			}
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
	line_export = line_exist(data->export, str);
	printf("env = %i | export = %i\n", line_env, line_export);
	if (line_env >= 0)
		erase_it(data, data->env, line_env);
	else if (line_export >= 0)
		erase_it(data, data->export, line_export);
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
		printf("Oui : %s\n", args[i]);
		unset_utils(data, args[i]);
		i++;
	}
	return (0);
}
