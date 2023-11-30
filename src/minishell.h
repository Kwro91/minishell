/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:10:34 by besalort          #+#    #+#             */
/*   Updated: 2023/11/30 15:32:05 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./pipex/pipex.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_envi
{
	char			**tab;
	struct s_envi	*next;
}t_envi;

typedef struct s_mdata
{
    char    **env;
	char	**export;
    char    **paths;
    char    *pwd;
	char	**unset;
	t_envi	*envi;
}   t_mdata;

//Init
void	init_built_int(t_mdata *data);

//Prompt
void    prompt(t_mdata *data, int ac, char **av, char **env);

//Path
void	ft_path_all(t_mdata *data, char **paths);
void	ft_path_no_env(t_mdata *data);
char	**ft_path_mini(char **env);
void    ft_free_lines(char	**lines);

//Free
void    ft_free_mini(t_mdata *data);
void	ft_free_adr(void *adr);
//IsCmd
int     is_echo(char **cmd_total);
int     is_exit(char **cmd_total, t_mdata *data);
int     is_pwd(char **cmd_total, t_mdata *data);
int     is_env(char **cmd_total, t_mdata *data);
int 	is_export(char **cmd_total, t_mdata *data);
int		is_unset(char **cmd_total, t_mdata *data);

//BUILT_IN

//Utils
int     nb_word(char **text);

//Echo
void    ft_echo(char **text);

//Env
void    env_setup(t_mdata *data, char **env);
void	env_cmd(t_mdata *data);

//Pwd
void	setup_pwd(t_mdata *data, char **env, int first);
void    pwd(t_mdata *data);

//Exit
void    exit_mini(t_mdata *data);

//Unset
int		ft_unset(char **args, t_mdata *mdata);
void	unset_option(t_mdata *data, char *arg);

//Export
void	export_cmd(t_mdata *data, char *line);
char	*modif_export(char *line);

//Signal
void	handle_signals(void);

#endif 