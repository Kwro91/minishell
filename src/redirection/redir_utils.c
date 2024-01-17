/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 15:54:38 by besalort          #+#    #+#             */
/*   Updated: 2024/01/17 18:06:38 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	open_out_files(t_mdata *data)
{
	int	i;

	i = 0;
	if (!data->out.files)
		return ;
	while (data->out.files[i])
	{
		if (data->out.fd > 1)
			close(data->out.fd);
		data->out.fd = open(data->out.files[i], O_RDWR | O_TRUNC | O_CREAT,
			S_IRWXU);
		printf("On open %s out file\n", data->out.files[i]);
		i++;
	}
}

void	open_in_files(t_mdata *data)
{
	int	i;

	i = 0;
	if (!data->in.files)
		return ;
	while (data->in.files[i])
	{
		if (data->in.fd > 1)
			close(data->in.fd);
		data->in.fd = open(data->in.files[i], O_RDONLY);
		printf("On open %s in file\n", data->out.files[i]);
			if (data->in.fd == 0)
			{
				ft_error(data, "minishell: ", 0);
				ft_error(data, data->in.files[i], 0);
				ft_error(data, ": no such file or directory\n", 0);
			}
		i++;
	}
}

void	ft_open_mfiles(t_mdata *data)
{
	if (data->here_doc == 0)
		open_in_files(data);
	else
		data->in.fd = open(".here_doc_tmp",
			O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	open_out_files(data);
}

int	get_count(t_mdata *data, int count)
{
	(void)data;
	(void)count;
	// if (data->here_doc == 1)
	// {
	// 	count += 2;
	// 	count += ft_strlen(data->eof);
	// }
	// if (data->in.files != NULL)
	// {
	// 	count++;
	// 	count += ft_strlen(data->in.files);
	// }
	// if (data->out.files != NULL)
	// {
	// 	count++;
	// 	count += ft_strlen(data->out.files);
	// }
	// printf("count = %i\n", count);
	return (count);
}

char	*redir_rewrite(t_mdata *data, char *line)
{
	int	count;

	count = 0;
	get_count(data, count);
	return (line);
}
