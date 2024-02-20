/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:43:20 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 13:05:07 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int str_to_cmp(char c, char *cmp)
{
	int	i;

	i = 0;
	while (cmp && cmp[i])
	{
		if (cmp[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	count_cmd(t_mdata *data, char *str, char *cmp)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (str && str[i])
	{
		while (str_to_cmp(str[i], cmp) == 1)
			i++;
		if (str[i] && str_to_cmp(str[i], cmp) == 0)
			wd++;
		if (str[i] == '"')
			i = split_dquote(data, str, i);
		else if (str[i] == '\'')
			i = split_squote(data, str, i);
		while (str[i] && str_to_cmp(str[i], cmp) == 0)
			i++;
	}
	return (wd);
}

static char	*ft_fill(t_mdata *data, char *src, size_t i, char *cmp)
{
	size_t	j;
	size_t	count;
	char	*str;

	j = i;
	while (src[j] && str_to_cmp(src[j], cmp) == 0)
	{
		if (src[j] == '"')
			j = split_dquote(data, src, j);
		else if (src[j] == '\'')
			j = split_squote(data, src, j);
		j++;
	}
	count = j - i;
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		ft_error(data, "Error: malloc\n", 1);
	j = 0;
	while (j < count)
	{
		str[j] = src[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

void	split1(t_mdata *data, char **tab, char *str, char *cmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str_to_cmp(str[i], cmp) == 1)
			i++;
		if (str[i] && str_to_cmp(str[i], cmp) == 0)
		{
			tab[j] = ft_fill(data, str, i, cmp);
			if (!tab[j])
				ft_error(data, "Error: malloc\n", 1);
			j++;
		}
		while (str[i] && str_to_cmp(str[i], cmp) == 0)
		{
			if (str[i] == '"')
				i = split_dquote(data, str, i);
			else if (str[i] == '\'')
				i = split_squote(data, str, i);
			i++;
		}
	}
	tab[j] = NULL;
}

char	**split_cmd(t_mdata *data, char *str, char *cmp)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_cmd(data, str, cmp) + 1));
	if (!tab)
		return (NULL);
	split1(data, tab, str, cmp);
	return (tab);
}
