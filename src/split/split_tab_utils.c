/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tab_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:40:48 by besalort          #+#    #+#             */
/*   Updated: 2024/03/24 19:19:23 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	use_tab(int *tab)
{
	int	i;

	i = 0;
	while (tab[i] != -1 && tab[i] > -2 && i < 4096)
		i++;
	if (i < 4094)
	{
		tab[i] = -2;
		tab[i + 1] = -2;	
	}
}

int	get_pos(t_mdata *data, int *tab)
{
	int	i;
	int	newpos;

	(void)data;
	i = 0;
	while (tab[i] == -2 && i < 4096)
		i++;
	printf("GET POS : i:%i: && tab[%i]:%i: && tab[%i]:%i:\n", i, i, tab[i], i + 1, tab[i + 1]);
	newpos = tab[i + 1];
	return (newpos);
}

t_arg	*new_arg_pos(t_mdata *data, int *tab, t_arg *arg, int pos)
{
	t_arg	*new;
	t_arg	*tmp;
	int		i;

	i = 0;
	new = NULL;
	tmp = arg;
	new = malloc(sizeof(t_arg));
	new->pos = pos;
	while (tab[i] == -2 && i < 4096)
		i++;
	new->len = tab[i] - pos;
	printf("i = %i && len = tab[i]:%i: - pos:%i: -1 = %i\n", i, tab[i], pos, new->len);
	if (new->len < 0)
		
	new->next = NULL;
	if (!new)
		ft_error(data, "Error: malloc", -1);
	if (tmp == NULL)
		return (new);
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (arg);
}

t_arg	*new_arg_tab(t_mdata *data, int *tab, t_arg *arg)
{
	t_arg	*new;
	t_arg	*tmp;
	int		i;

	i = 0;
	tmp = arg;
	new = malloc(sizeof(t_arg));
	if (!new)
		ft_error(data, "Error: malloc", -1);
	while (tab[i] >= -2 && tab[i] != -1)
		i++;
	new->len = tab[i + 1] - tab[i];
	new->pos = tab[i];
	new->next = NULL;
	if (tmp == NULL)
		return (new);
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (arg);
}

t_arg	*get_arg(t_mdata *data, int *tab, int nb)
{
	int		i;
	int		pos;
	t_arg	*new;

	new = NULL;
	i = 0;
	pos = 0;
	while (i < nb)
	{
		if (i < nb)
		{
			new = new_arg_pos(data, tab, new, pos);
			i++;
		}
		if (i < nb)
		{
			new = new_arg_tab(data, tab, new);
			i++;
		}
		pos = get_pos(data, tab);
		use_tab(tab);
	}
	return (new);
}
