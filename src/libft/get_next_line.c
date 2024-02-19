/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:16:53 by besalort          #+#    #+#             */
/*   Updated: 2023/06/23 17:00:57 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../libft/libft.h"

static	char	*ft_newline(char **stock, char **line)
{
	char	*tmp;
	int		i;

	i = 0;
	while ((*stock)[i] != '\n' && (*stock)[i])
		i++;
	if ((*stock)[i] == '\n')
	{		
		*line = ft_substr(*stock, 0, i + 1);
		tmp = ft_strdup((*stock) + i + 1);
		free(*stock);
		*stock = tmp;
		if ((*stock)[0] == 0)
		{
			free(*stock);
			*stock = NULL;
		}
	}
	else
	{
		*line = ft_strdup(*stock);
		free(*stock);
		*stock = NULL;
	}
	return (*line);
}

static	char	*ft_verif(char **stock, int nb, int fd, char **line)
{
	if (nb < 0 || fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if ((*stock) == NULL && nb == 0)
		return (NULL);
	return (ft_newline(stock, line));
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	char		*new;
	char		*line;
	static char	*stock;
	int			nb;

	if (BUFFER_SIZE <= 0 || fd < 0 || BUFFER_SIZE >= 8000000 || fd > 1024)
		return (NULL);
	nb = read(fd, buf, BUFFER_SIZE);
	while (nb > 0 && BUFFER_SIZE > 0 && fd >= 0)
	{
		buf[nb] = '\0';
		if (!stock)
			stock = ft_strdup(buf);
		else
		{
			new = ft_strjoin(stock, buf);
			free(stock);
			stock = new;
		}
		if (ft_strchr(stock, '\n'))
			return (ft_newline(&stock, &line));
		nb = read(fd, buf, BUFFER_SIZE);
	}
	return (ft_verif(&stock, nb, fd, &line));
}
