/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: besalort <besalort@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 16:27:50 by besalort          #+#    #+#             */
/*   Updated: 2024/01/11 17:57:28 by besalort         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <errno.h>
# include <fcntl.h>

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

typedef struct s_lst
{
	char	*cmd;
	char	**command;
	void	*next;
}	t_lst;

typedef struct s_data
{
	int		ac;
	char	**av;
	char	**env;
}	t_data;

typedef struct s_file
{
	char	*file;
	int		fd;
}	t_file;

typedef struct s_pipex
{
	int			status;
	int			is_env;
	int			cmds;
	int			pipes[2];
	int			fd_in;
	int			here_doc;
	char		**paths;
	char		*eof;
	pid_t		child[2];
	t_file		file1;
	t_file		file2;
	t_lst		*lst;
	t_data		data;
}	t_pipex;
// FT_CHECK.C //
void	ft_open_files(t_pipex *data, char *file1, char *file2);
// FT_ACCESS.C //
char	*ft_access_cmd(t_pipex *data, char *cmd);
char	*ft_modify_cmd(char *cmd);
// FT_CMD.C //
char	**ft_command(char *command);
// FT_FREE.C //
void	close_give_fd(int fd1, int fd2);
void	ft_free_here_doc(void);
void	delete_list(t_lst *lst);
void	ft_free_paths(char **paths);
void	ft_free(t_pipex *data);
// FT_HERE_DOC.C //
int		ft_check_here_doc(t_pipex *data);
void	ft_here_doc(t_pipex *data);
// FT_PATH.C //
char	**ft_path(char **env);
void	ft_path_no_environement(t_pipex *data);
void	ft_path_complete(t_pipex *data, char **paths);
// FT_LIST.C //
t_lst	*createlist(int size, char **command);
// FT_LOAD.C //
void	ft_listload(t_pipex *data, char **av);
void	ft_load_av(t_pipex *data, int ac, char **av);
void	ft_load_env(t_pipex *data, char **env);
void	ft_load_values(t_pipex *data, int ac, char **av);
int		ft_load(t_pipex *data, int ac, char **av, char **env);
// FT_PIPEX.C //
int		ft_pipex(int ac, char **av, char **env, t_mdata *mini);
void	ft_msg(char *msg);
// PROCESSES.C //
void	ft_first_process(t_pipex *data, char **cmdp, int pipes[2], t_mdata *mini);
void	ft_last_process(t_pipex *data, char **cmdp, int pipes[2], t_mdata *mini);
void	ft_processes(t_pipex *data, char **cmdp, int pipes[2], t_mdata *mini);
// FT_RUN.C //
void	run_first(t_pipex *data, t_lst *tmp, t_mdata *mini);
t_lst	*run_other(t_pipex *data, t_lst *tmp, t_mdata *mini);
void	run_last(t_pipex *data, t_lst *tmp, t_mdata *mini);
void	wait_childs(t_pipex *data);
void	run_processes(t_pipex *data, t_mdata *mini);
#endif
