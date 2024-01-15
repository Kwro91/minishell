/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 14:15:35 by besalort          #+#    #+#             */
/*   Updated: 2024/01/15 16:59:02 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	verif_cmd(t_mdata *data, char **cmd_total, char **env)
{
	(void)env;
	if (is_echo(cmd_total) == 1)
		return (1);
	else if (is_pwd(cmd_total, data) == 1)
		return (1);
	else if (is_exit(cmd_total, data) == 1)
		return (1);
	else if (is_env(cmd_total, data) == 1)
		return (1);
	else if (is_export(cmd_total, data) == 1)
		return (1);
	else if (is_unset(cmd_total, data) == 1)
		return (1);
	else if (is_cd(cmd_total, data) == 1)
		return (1);
	return (0);
}

int	nb_word(char **text)
{
	int	i;

	i = 0;
	while (text && text[i])
		i++;
	return (i);
}

void	good_print(char	*line)
{
	int	i;
	int	equal;

	i = 0;
	equal = 0;
	if (!line)
		return ;
	while (line[i])
	{
		ft_printf("%c", line[i]);
		if (line[i] == '=' && equal == 0)
		{
			equal = 1;
			ft_printf("\"");
		}
		i++;
	}
	if (equal == 1)
		ft_printf("\"");
}
