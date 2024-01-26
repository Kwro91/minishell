/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:10:34 by besalort          #+#    #+#             */
/*   Updated: 2024/01/26 15:38:46 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include "./pipex/pipex.h"
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int g_retval;

typedef struct s_envi
{
	char			**tab;
	struct s_envi	*next;
}t_envi;

typedef struct s_string
{
	char			*str;
	int				type;
	int				*dollar;
	struct s_string	*next;
}t_string;

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
int		is_cd(char **cmd_total, t_mdata *data);

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
void	export_cmd(t_mdata *data, char **line);
int		do_line_exist(char **export, char *line);
int		reset_line(char **export, char *line);
char	**modif_export(char **line);
char	*modif_utils(char *line);

//Cd
void	cd_cmd(t_mdata *data, char *line);

//Signal
void	handle_signals(void);

//Parsing
// int		parsing(char *cmd);

//Dollar
void	handle_dollar(t_mdata *data, char *cmd);


//Quotes
int		check_quotes(char *str);
char	*remove_quotes(char *cmd_total);
void	remove_double(char *cmd_total, char *new_cmd, int i, int j);
void	remove_single(char *cmd_total, char *new_cmd, int i, int j);
int		nb_quotes(char *cmd_total);

#endif 