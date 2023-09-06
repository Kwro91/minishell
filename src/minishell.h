/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:10:34 by besalort          #+#    #+#             */
/*   Updated: 2023/09/06 17:52:12 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./pipex/pipex.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_mdata
{
    char    **paths;
    char    *pwd;
}   t_mdata;

//Prompt
void    prompt(int ac, char **av, char **env);

//Path
void	ft_path_all(t_mdata *data, char **paths);
void	ft_path_no_env(t_mdata *data);
char	**ft_path_mini(char **env);
void    ft_free_mini(t_mdata *data);

//IsCmd
int     is_exit(char **cmd_total, t_mdata *data);
int     is_echo(char **cmd_total);
int     is_pwd(char **cmd_total, t_mdata *data);

//Echo
void    ft_echo(char **text);

//Pwd
void	setup_pwd(t_mdata *data, char **env);
void    pwd(t_mdata *data);

//Exit
void    exit_mini(t_mdata *data);

//Signal
void	handle_signals(void);
#endif 