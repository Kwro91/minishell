/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:08:19 by besalort          #+#    #+#             */
/*   Updated: 2024/02/29 12:02:40 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	while (text && text[i] && ft_strncmp(text[i], "-n", 2) == 0)
		i++;
	while (text[i])
	{
		write(1, text[i], ft_strlen(text[i]));
		i++;
		if (text[i])
			write(1, " ", 1);
	}
	if (text && ft_strncmp(text[0], "-n", 2) != 0)
		write(1, "\n", 1);
	g_retval = 0;
}
