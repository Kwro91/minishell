/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:41:18 by afontain          #+#    #+#             */
/*   Updated: 2023/11/30 14:57:10 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_same(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (!s1[i] && (!s2[i] || (s2[i] == '+' && !s2[i + 1])))
		return (1);
	return (0);
}

t_envi	*search_node(t_envi *envi, char *str)
{
	t_envi	*travel;

	travel = envi;
	if (!str)
		return (NULL);
	while (travel)
	{
		if (is_same(travel->tab[0], str))
			return (travel);
		travel = travel->next;
	}
	return (NULL);
}

void	unset_option(t_mdata *data, char *arg)
{
	t_envi	*before;
	t_envi	*node;

	before = data->envi;
	node = search_node(data->envi, arg);
	if (node)
	{
		while (before->next && !strcmp(before->next->tab[0], arg))
			before = before->next;
		if (!before->next)
			data->envi = node->next;
		else
			before->next = node->next;
		ft_free_adr(node);
	}
}

int	ft_unset(char **args, t_mdata *data)
{
	int		i;

	i = 0;
	if (!args || !args[0])
		return (0);
	while (args[i])
	{
		unset_option(data, args[i]);
		i++;
	}
	return (0);
}
