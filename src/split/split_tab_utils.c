/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tab_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 15:40:48 by besalort          #+#    #+#             */
/*   Updated: 2024/03/25 20:37:52 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		is_tab(int	*tab)
{
	int	i;

	i = 0;
	while (i < 4096 && tab[i] == -2)
	{
		i++;
	}
	printf("SHOW TAB[%i]:%i:\n", i, tab[i]);
	return (tab[i]);
}

void	use_tab(int *tab)
{
	int	i;

	i = 0;
	while (i < 4096 && tab[i] == -2)
	{
		// printf("SHOW TAB[%i]:%i:\n", i, tab[i]);
		i++;
	}
	if (i < 4094)
	{
		tab[i] = -2;
		tab[i + 1] = -2;	
	}
}

int	get_pos(t_mdata *data, int *tab, t_arg *arg)
{
	int		i;
	int		newpos;
	t_arg	*tmp;

	(void)data;
	i = 0;
	tmp = arg;
	while (tab[i] == -2 && i < 4096)
		i++;
	// printf("GET POS : i:%i: && tab[%i]:%i: && tab[%i]:%i:\n", i, i, tab[i], i + 1, tab[i + 1]);
	if (tab[i] == -1)
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		newpos = (tmp->pos + tmp->len);
	}
	else
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
	while (tab[i] == -2 && i < 4096)
		i++;
	new->len = tab[i] - pos;
	if (new->len < 0)
		new->len = 0;
	new->pos = pos;
	new->tab = 0;
	new->next = NULL;
	// printf("i = %i && len = tab[i]:%i: - pos:%i: -1 = %i\n", i, tab[i], pos, new->len);
	if (new->len <= 0)
		printf("La len est < a 0\n");
	if (!new)
		ft_error(data, "Error: malloc", -1);
	if (tmp == NULL)
		return (new);
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (new->pos < 0)
			new->pos = (tmp->pos + tmp->len);
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
	while (i < 4096 && tab[i] == -2)
		i++;
	new->len = tab[i + 1] - tab[i];
	new->pos = tab[i];
	new->tab = 1;
	new->next = NULL;
	if (tmp == NULL)
		return (new);
	else
	{
		while (tmp && tmp->next)
			tmp = tmp->next;
		if (new->pos < 0)
			new->pos = (tmp->pos + tmp->len);
		tmp->next = new;
	}
	return (arg);
}



t_arg	*get_arg(t_mdata *data, int *tab, int nb)
{
	int		i;
	int		count;
	int		pos;
	t_arg	*new;
	// int		value;

	new = NULL;
	count = 0;
	pos = 0;
	while (count < nb + 1)
	{
		i = 0;
		// tmp = new;
		// if (new && pos != 0)
		// {
		// 	while (tmp->next)
		// 		tmp = tmp->next;
		// }
		while (i < 4096 && tab[i] == -2)
			i++;
		if (pos < tab[i] || tab[i] == -1)
		{
			// value = 0;
			new = new_arg_pos(data, tab, new, pos);
			i++;
		}
		else
		{
			if (is_tab(tab) != -1)
			{
				// value = 1;
				printf("OUI !!\n");
				new = new_arg_tab(data, tab, new);
				i++;
				use_tab(tab);
			}
		}
		count++;
		// if (i < nb)
		// if (i < nb)
		// }
		pos = get_pos(data, tab, new);
	}
	return (new);
}
