/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 17:43:20 by besalort          #+#    #+#             */
/*   Updated: 2024/02/20 18:13:46 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

char	*fill_cmd(t_mdata *data, char *src, int i, char *cmp)
{
	int		j;
	int		len;
	int		count;
	char	*str;

	j = i;
	len = ft_strlen(src);
	while (j >= 0 && j < len && (str_to_cmp(src[j], cmp) == 0))
	{
		printf("j:%i:\n", j);
		if (src[j] == '"')
			j = split_dquote(data, src, j);
		else if (src[j] == '\'')
			j = split_squote(data, src, j);
		j++;
	}
	count = j - i + 1;
	str = malloc(sizeof(char) * (count + 1));
	if (!str)
		ft_error(data, "Error: malloc\n", 1);
	j = 0;
	while (j < count)
		str[j++] = src[i++];
	str[j] = '\0';
	return (str);
}

int	split2(t_mdata *data, int i, char *str, char *cmp)
{
	int len;

	len = ft_strlen(str);
	while (i >= 0 && i < len && str_to_cmp(str[i], cmp) == 0)
	{
		if (str[i] == '"')
			i = split_dquote(data, str, i);
		else if (str[i] == '\'')
			i = split_squote(data, str, i);
		i++;
	}
	return (i);
}

void	split1(t_mdata *data, char **tab, char *str, char *cmp)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && str_to_cmp(str[i], cmp) == 1)
			i++;
		if (str[i] && str_to_cmp(str[i], cmp) == 0)
		{
			tab[j] = fill_cmd(data, str, i, cmp);
			if (!tab[j])
				ft_error(data, "Error: malloc\n", 1);
			j++;
		}
		i = split2(data, i, str, cmp);
		// while (str[i] && str_to_cmp(str[i], cmp) == 0)
		// {
			// if (str[i] == '"')
			// 	i = split_dquote(data, str, i);
			// else if (str[i] == '\'')
			// 	i = split_squote(data, str, i);
			// i++;
		// }
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
