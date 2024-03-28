/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 14:25:20 by besalort          #+#    #+#             */
/*   Updated: 2024/03/25 20:00:50 by besalort         ###   ########.fr       */
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

char	**split_copy_add(t_mdata *data, char **base, char **add, int size)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (base[j] != NULL)
		j++;
	printf("DEBUT:\n");
	while (add && add[i] && i < size)
	{
		printf("PTAB :%s:\n", add[i]);
		base[j] = ft_strdup(add[i]);
		if (!base[j])
			ft_error(data, "Error: strdup\n", -1);
		j++;
		i++;
	}
	return (base);
}

void	split_arg_pos(t_mdata *data, t_arg *arg, char *str, char **new)
{
	int		cmd;
	char	**split;
	char	*newstr;

	newstr = str;
	if (arg->len <= 0)
		arg->len = ft_strlen(str);
	else
	{
		newstr = ft_strndup(data, &str[arg->pos], arg->len);
		if (!newstr)
			ft_error(data, "Error: strdup\n", -1);
	}
	printf("NEWSTR:%s:\n", newstr);
	cmd = count_cmd(data, newstr, " \t");
	if (!new)
		new = ft_calloc(sizeof(char *), (cmd + 1));
	split = split_cmd(data, newstr, " \t");
	if (!split)
		ft_error(data, "Error: split\n", -1);
	split_copy_add(data, new, split, nb_word(split));
}

char	*split_arg_tab(t_mdata *data, t_arg *arg, char *str)
{
	t_arg	*tmp;
	// char	**new;
	// int		i;
	
	// (void)data;
	// (void)str;
	tmp = arg;
	// i = 0;
	// if (tmp)
	// {
	// 	ft_error(data, "TMP :", 0);
	// 	print_text(str, tmp->pos, tmp->len);
	// 	printf(": tmp->pos:%i: && tmp->len:%i:\n", tmp->pos, tmp->len);
		
	// 	if (tmp->len < 0 || tmp->pos == -1)
	// 	{
	// 		while (i < 4096 && tab[i] == -2)
	// 			i++;
	// 		printf("A la pos:%i:, on doit tout split\n", tab[i + 1]);
	// 	}	
	// }
	char	*new;

	new = NULL;
	if (tmp)
	{
		new = ft_strndup(data, &str[tmp->pos], tmp->len);
		if (!new)
			ft_error(data, "Error strndup\n", -1);
		printf("STAB :%s:\n", new);
		// if (tmp->len < 0 || tmp->pos == -1)
	}
	return (new);
}

char	**split_arg_utils(t_mdata *data, t_arg *arg, char *str, int len)
{
	char	**new;
	char	*tmp2;
	t_arg	*tmp;
	int		i;
	int		last;
	
	tmp = arg;
	last = 1;
	new = ft_calloc(sizeof(char *), len + 1);
	while (tmp)
	{
		i = 0;
		tmp2 = NULL;
		if (tmp->tab == 1)
		{
			tmp2 = split_arg_tab(data, tmp, str);
			while(new && new[i])
				i++;
			new[i] = ft_strdup(tmp2);
			ft_free_me(tmp2);
		}
		else if (tmp->tab == 0 && last == 1)
		{
			if (tmp->len <= 0)
				split_arg_pos(data, tmp, &str[tmp->pos], new);
			else
				split_arg_pos(data, tmp, str, new);
			// 	printf("PTAB :%i -> %i:(END)\n", tmp->pos, (int)(ft_strlen(str) - 1));
			// else
			// 	printf("PTAB :%i -> %i:\n", tmp->pos, (tmp->pos + tmp->len - 1));
		}
		// tmp2 = split_arg_tab(data, tmp, str);
		last = tmp->tab;
		tmp = tmp->next;
	}
	i = 0;
	printf("ON AFFICHE A LA FIN\n");
	while (new && new[i])
	{
		printf(":%s:\n", new[i]);
		i++;
	}
	return (new);
}

char	**split_arg(t_mdata *data, char *str, int *tab, int len)
{
	char	**new;
	t_arg	*arg;

	arg = NULL;
	if (tab[0] == -1 || len == 1)
	{
		printf("cmd[0] == %s\n", str);
		// new = split_cmd(data, str, " \t");
		new = malloc(sizeof(char *) * 2);
		new[0] = ft_strdup(str);
		new[1] = NULL;
		return (new);
	}
	print__all_line(str);
	print_tab(tab);
	// len = count_arg(data, str, tab);
	printf("ON A :%i: ARGS PREVUS\n", len);
	arg = get_arg(data, tab, len);
	t_arg *tmp;
	tmp = arg;
	while (tmp)
	{
		printf("pos :%i: && len :%i: && tab :%i:\n", tmp->pos, tmp->len, tmp->tab);
		tmp = tmp->next;
	}
	new = split_arg_utils(data, arg, str, len);
	return (new);
}
