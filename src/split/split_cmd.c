/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:43:20 by besalort          #+#    #+#             */
/*   Updated: 2024/02/19 20:22:44 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_cmd(t_mdata *data, char *str, char c)
{
	int	i;
	int	wd;

	i = 0;
	wd = 0;
	while (str && str[i]) //ICI ET PARTOUT FAUT CHANGER LE != C avec une fct qui prends compare avec une chaine de caractere
	{
		while (str[i] == c)
			i++;
		if (str[i] && str[i] != c)
			wd++;
		if (str[i] == '"')
			i = split_dquote(data, str, i);
		else if (str[i] == '\'')
			i = split_squote(data, str, i);
		while (str[i] && str[i] != c)
			i++;
	}
	return (wd);
}

static char	*ft_fill(t_mdata *data, char *src, size_t i, char c)
{
	size_t	j;
	size_t	count;
	char	*str;

	j = i;
	while (src[j] && src[j] != c)
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

void	split1(t_mdata *data, char **tab, char *str, char c)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i] && str[i] != c)
		{
			tab[j] = ft_fill(data, str, i, c);
			if (!tab[j])
				ft_error(data, "Error: malloc\n", 1);
			j++;
		}
		while (str[i] && str[i] != c)
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

char	**split_cmd(t_mdata *data, char *str, char c)
{
	char	**tab;

	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_cmd(data, str, c) + 1));
	if (!tab)
		return (NULL);
	split1(data, tab, str, c);
	return (tab);
}
