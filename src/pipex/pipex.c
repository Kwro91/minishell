/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 14:18:52 by besalort          #+#    #+#             */
/*   Updated: 2024/01/11 17:03:32 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_msg(char *msg)
{
	ft_putstr_fd(msg, 2);
}

int	ft_pipex(int ac, char **av, char **env)
{
	t_pipex	data;
	int		value;

	data = (t_pipex){};
	value = 0;
	if (ft_load(&data, ac, av, env) == -1)
		return (ft_msg("Error, args\n"), data.status);
	ft_path_complete(&data, ft_path(env));
	ft_open_files(&data, data.file1.file, data.file2.file);
	run_processes(&data);
	value = data.status;
	ft_free(&data);
	return (value);
}

// int	main(int ac, char **av, char **env)
// {
// 	if (ac >= 5)
// 		return (ft_pipex(ac, av, env));
// 	else
// 		ft_msg("Error, Wrong nb of arg\n");
// }
