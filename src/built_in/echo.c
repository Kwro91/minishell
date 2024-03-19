/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:08:19 by besalort          #+#    #+#             */
/*   Updated: 2024/03/19 15:58:20 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_echo(char *text)
{
	int i;

	i = 1;
	if (ft_strncmp(text, "-n", 2) != 0)
			return (0);
	while (text && text[i] == 'n' )
		i++;
	if (text[i] == '\0')
		return (1);
	return (0);
}

int	echo_bis(char **text, int nb)
{
	char	*word0;
	char	*wordn;

	word0 = "-n\0";
	wordn = "-n\n";
	if (nb == 0)
	{
		write(1, "\n", 1);
		return (1);
	}
	if (nb == 1)
	{
		if (strncmp(text[0], word0, 3) == 0 || strncmp(text[0], wordn, 3) == 0)
			return (1);
	}
	return (0);
}

void	ft_echo(char **text)
{
	int	i;
	int	nb;

	i = 0;
	nb = nb_word(text);
	if (echo_bis(text, nb) == 1)
		return ;
	while (text && text[i] && verif_echo(text[i]) == 1)
			i++;
	while (text[i])
	{
		if (i != nb - 1)
			write(1, text[i], ft_strlen(text[i]));
		else
			write(1, text[i], ft_strlen(text[i]));
		i++;
		if (text[i])
			write(1, " ", 1);
	}
	if (text && ft_strncmp(text[0], "-n\0", 3) != 0)
	{
		if (verif_echo(text[0]) == 0)
			write(1, "\n", 1);
	}
	g_retval = 0;
}
