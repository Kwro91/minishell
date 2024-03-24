/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:25:20 by besalort          #+#    #+#             */
/*   Updated: 2024/03/24 19:12:36 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//une fonction qui ajoute une string a la fin d'un char**

//une fonction qui split jusque n position et ensuite appelle la premiere puis recommence jusque la fin

void	str_add_next(t_mdata *data, char **arg, char *new, int len)
{
	int	i;

	i = 0;
	while (arg && arg[i] && i < len)
		i++;
	if (i < len)
		arg[i] = ft_strdup(new);
			if (!arg[i])
				ft_error(data, "Error: strdup\n", -1);
}

int	count_arg(t_mdata *data, char *str, int *tab)
{
	int	count;
	int	i;

	i = 0;
	count = count_cmd(data, str, " ");
	printf("COUNT :%i\n", count);
	while (i < 4096 && tab[i] > -1)
		i++;
	i = i / 2;
	count += i;
	return (count);
}

// spliter sur strndup
// passer les arg du tab a -2 quand utilise

// export coucou=" sfgsfgh"  slt="echo      hey"   -->   export ; slt= ; echo     hey ;

void	print__all_line(char *str)
{
	int i = 0;
	
	write(2, "\n",1);
	while (str[i])
	{
		write(2, &str[i], 1);
		write(2, "|",1);
		i++;
	}
	write(2, "\n",1);
	i = 0;
	while (str[i])
	{
		write(2, ft_itoa(i), 1);
		write(2, "|",1);
		i++;
	}
	write(2, "\n",1);
	write(2, "\n",1);
}

void	print_tab(int *tab)
{
	int i = 0;

	while (i < 4096 && tab[i] > -1)
	{
		printf("tab[%i]=:%i:\n", i, tab[i]);
		i++;
	}
}

void	print_text(char *str, int pos, int len)
{
	int	i;

	i = 0;
	while(i < len)
	{
		write(2, &str[pos + i], 1);
		i++;
	}
}

char	**split_tab_utils(t_mdata *data, char *str, t_arg *arg)
{
	t_arg	*tmp;
	
	(void)data;
	(void)str;
	tmp = arg;
	while (tmp)
	{
		ft_error(data, "TMP :", 0);
		print_text(str, tmp->pos, tmp->len);
		printf(": tmp->pos:%i: && tmp->len:%i:\n", tmp->pos, tmp->len);
		if (tmp->len < 0)
			printf("A la pos:%i:, on doit tout split\n", tmp->pos);
		tmp = tmp->next;	
	}
	return (NULL);
}

char	**split_tab(t_mdata *data, char *str, int *tab, int len)
{
	char	**new;
	t_arg	*arg;
	
	if (tab[0] == -1)
	{
		printf("On split tout normalement\n");
		new = split_cmd(data, str, " \t");
		return (new);
	}
	print__all_line(str);
	print_tab(tab);
	// len = count_arg(data, str, tab);
	printf("ON A :%i: ARGS PREVUS\n", len);
	arg = get_arg(data, tab, len);
	new = split_tab_utils(data, str, arg);
	return (new);
}
