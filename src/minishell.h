/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afontain <afontain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 14:10:34 by besalort          #+#    #+#             */
/*   Updated: 2024/02/13 18:10:24 by afontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

extern int	g_retval;

typedef struct s_files
{
	int		here_doc;
	int		fd;
	char	*files;
	void	*next;
}	t_files;

typedef struct s_envi
{
	char			**tab;
	struct s_envi	*next;
}t_envi;

typedef struct s_command
{
	char	*line;
	char	**cmd;
	int		good;
	t_files	*in;
	t_files	*out;
	void	*next;
}	t_command;

typedef struct s_mdata
{
	char		**env;
	char		**paths;
	char		**export;
	char		**unset;
	char		*pwd;
	int			nb_cmd;
	int			pipes[2];
	int			pipe_save;
	t_command	*cmd;
	t_envi		*envi;
}	t_mdata;

typedef struct s_string
{
	char			*str;
	int				type;
	int				*dollar;
	struct s_string	*next;
}	t_string;

typedef struct s_quotes
{
	int	quote;
	int	squote;
}	t_quotes;

//Init
void		init_built_int(t_mdata *data);

//Prompt
void		prompt(t_mdata *data, char **env);
void		end_loop(t_mdata *data);
void		close_end(t_mdata *data);
//Path
void		ft_path_all(t_mdata *data, char **paths);
void		ft_path_no_env(t_mdata *data);
char		**ft_path_mini(char **env);
void		ft_free_lines(char	**lines);

//Free
void		ft_free_mini(t_mdata *data);
void		ft_free_adr(void *adr);
void		ft_free_files(t_files *files);
void		ft_error(t_mdata *data, char *line, int close);
//IsCmd
int			verif_cmd(t_mdata *data, t_command *cmd);
int			is_echo(char **cmd_total);
int			is_exit(char **cmd_total, t_mdata *data);
int			is_pwd(char **cmd_total, t_mdata *data);
int			is_env(char **cmd_total, t_mdata *data);
int			is_export(char **cmd_total, t_mdata *data);
int			is_unset(char **cmd_total, t_mdata *data);
int			is_cd(char **cmd_total, t_mdata *data);

//BUILT_IN

//Utils
int			nb_word(char **text);
void		good_print(char	*line);

//Echo
void		ft_echo(char **text);

//Env
void		env_setup(t_mdata *data, char **env);
void		env_cmd(t_mdata *data);

//Pwd
void		setup_pwd(t_mdata *data, char **env, int first);
void		pwd(t_mdata *data);
void		add_pwd(t_mdata *data);

//Exit
void		exit_mini(t_mdata *data);

//Unset
int			ft_unset(char **args, t_mdata *mdata);

//Export
void		export_cmd(t_mdata *data, char **line);
int			do_line_exist(char **export, char *line);
int			reset_line(t_mdata *data, char **export, char *line);
int			check_export_line(t_mdata *data, char *line, int show);
void		error_export(t_mdata *data, char *error);

//Cd
void		cd_cmd(t_mdata *data, char *line);

//Signal
void		handle_signals(void);

//EXECUTION
char		*ft_access_mini(t_mdata *data, char *cmd);
void		launch_cmd(t_mdata *data, t_command *cmd);

//REDIRECTION
int			redir(t_mdata *data, t_command *cmd);
char		*next_word(t_mdata *data, char *line);
char		*dup_word(t_mdata *data, char	*line, int len);
void		sub_files(t_mdata *data, t_command *cmd);
void		close_all_files(t_mdata *data, t_command *cmd);
void		close_two(t_mdata *data, int fd1, int fd2);
void		ft_mhere_doc(t_mdata *data, t_files *file);
t_files		*get_new_file(t_mdata *data, char *line, int here_doc);
t_files		*create_new_files(t_mdata *data, t_files *files,
				char *line, int hd);

// char	*is_here_doc(t_mdata *data, char *line);
void		is_fd_in(t_mdata *data, t_command *cmd);
void		is_fd_out(t_mdata *data, t_command *cmd);
char		*redir_rewrite(t_mdata *data, t_command *cmd);
void		ft_open_mfiles(t_mdata *data, t_command *cmd);
//PARSE
void		split_parse(t_mdata *data, char *line);
int			check_before(t_mdata *data, char *line);
int			check_line_pipe(t_mdata *data, t_command *cmd);

//Parsing
void		parse_cmd(t_mdata *data, t_command *cmd);

//Dollar
int			handle_dollar(t_mdata *data, t_command *cmd, int i);

//Quotes
int			check_quotes(char *str);
char		*remove_quotes(t_command *cmd);
void		remove_double(char *cmd_total, char *new_cmd, int i, int j);
void		remove_single(char *cmd_total, char *new_cmd, int i, int j);
int			nb_quotes(char *cmd_total);

//Pipe
void		mpipex(t_mdata *data);
void		ft_first_child(t_mdata *data, t_command *cmd, char *path);
void		ft_mid_childs(t_mdata *data, t_command *cmd, char *path);
void		ft_last_child(t_mdata *data, t_command *cmd, char *path);
void		rfirst(t_mdata	*data, t_command *cmd);
t_command	*rmiddle(t_mdata *data, t_command *cmd);
void		rlast(t_mdata *data, t_command *cmd);
void		mwait_childs(t_mdata *data);
void		run_all(t_mdata *data);
#endif 