/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 12:52:09 by afontain          #+#    #+#             */
/*   Updated: 2024/02/12 17:40:29 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdupfrom(char *src, int i)
{
	char	*dest;

	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * ft_strlen((const char *)src) - i + 1);
	if (!dest)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdupuntil(char *src, int i)
{
	char	*dest;
	int j;
	
	j = 0;
	if (!src)
		return (NULL);
	dest = malloc (sizeof(char) * i + 1);
	if (!dest)
		return (0);
	while (src[j] && j < i)
	{
		dest[j] = src[j];
		j++;
	}
	dest[j] = '\0';
	return (dest);
}

char	*replace_retval(char *cmd, int i)
{
	char *retu;
	char *resu;
	char *avant;
	char *apres;
	char	*new;
	
	retu = ft_itoa(g_retval);
	avant = ft_strdupuntil(cmd, i);
	resu = ft_strjoin(avant, retu);
	free(avant);
	// apres = ft_strdupfrom(resu, i + ft_strlen(retu));
	apres = ft_strdup(&cmd[i + 2]);
	new = ft_strjoin(resu, apres);
	free(retu);
	free(resu);
	free(apres);
	if (new)
		ft_printf("newline:%s\n", new);
	return (new);
}

// char	*replace_dollar(t_envi envi, char *cmd, int i)
// {
	
// }

void	handle_dollar(t_mdata *data, char *cmd)
{
	char	*res;
	// int		nb_dollar;
	int		i;

	(void) data;
	i = 0;
	// nb_dollar = 0;
	while (cmd[i])
	{
		if (cmd[i] == '$')
		{
			// if (nb_dollar == 1)
			// {
				if (cmd[i+1] == '?')
				{
					res = replace_retval(cmd, i);
					// free(cmd);
					cmd = res;
				}
				// else
				// 	res = replace_dollar(data->envi, cmd, i);
				// free(cmd);
				// cmd = res;
		}
		i++;	// nb_dollar++;
	}
	
}
