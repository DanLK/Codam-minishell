/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execution.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 14:21:08 by rojornod      #+#    #+#                 */
/*   Updated: 2025/06/19 12:06:10 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <sys/ioctl.h>
#include "../../libft/libft.h"
#include "../../parser/include/parser.h"
#include "../../lexer/include/lexer.h"

typedef struct s_vars
{
	char			*name;
	char			*value;
	int				exported;
	int				hidden;
	struct s_vars	*next;
}	t_vars;

typedef struct s_info
{
	int		exit_code;
	int		hd_count;
	int		cur_hd;
}	t_info;

//directories
char			*get_home_dir(void);

//history
// void			create_history_file(void);
// void			write_history_file(char *read);

//builtins
int				echo_builtin(char **tokens);
int				pwd_builtin(void);
int				cd_builtin(char *command, t_vars *vars);
int				export_builtin(t_vars **head, char *var_name, char *var_value);
int				unset_builtin(t_vars **head, char *var_name);
int				exit_builtin(t_vars *vars, t_info *info, int exit_code);
int				env_builtin(t_vars *head);

//builtins utils
void			set_exp_value(t_vars *temp, char *var_value);

//variables
t_vars			*add_var(t_vars **head, char *var_name, char *var_value,
					int exp);
t_vars			*create_var(char *name, char *value, int exp);
t_vars			*find_vars(t_vars *head, char *var_name);
void			copy_env(t_vars **head, char **envp);
void			edit_var(t_vars *vars, char *var_name, char *var_value);

//utils
int				ft_strcmp(char *s1, char *s2);
void			free_array(char **array);
void			free_vars(t_vars *head);
char			**convert_env(t_vars *head);

//signals
void			signal_action(void);
int				heredoc_action(void);
int				child_proc_action(void);
int				ignore_sig_action(void);
void			signal_handler(int signal);
void			child_proc_handler(int signal);
void			heredoc_handler(int signal);
int				get_signal_received(void);
void			reset_signal(void);
void			init_sig_heredoc(void);
void			res_sig(void);

//external commands
char			*find_path(t_vars *head, char *command);
int				exec_external_com(t_vars *head, char **cmd,
					int size, t_info *info);

//child process
int				create_child_proc(t_vars *vars, char **cmd, char *path,
					int size);
int				child_process(char *path, char **argv, char **env_copy);

//errors
char			*error_mssg(char *file, char *type);
void			not_found_error(char *argv);
void			permission_error(char *path);
void			is_directory_error(char *path);
void			no_such_file_error(char *argv);

//initializing
t_vars			*initialize_data(void);
t_info			*initialize_info(t_vars *vars, char **envp);