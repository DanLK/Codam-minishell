/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:08 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/11 12:44:26 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include "../../libft/libft.h"
#include "../../parser/include/parser.h"
#include "../../lexer/include/lexer.h"

#define STDIN  0
#define STDOUT 1

typedef struct s_vars
{
	char			*name;
	char			*value;
	int				exported;
	int				hidden;
	struct s_vars	*next;
}	t_vars;

typedef struct s_shell_info
{
	int		last_return_code;
	char	*home_dir;
	int		fdin;
	int		fdout;
	int		hd_count;
	int		cur_hd;
}	t_info;

//directories
char			*get_home_dir(void);

//history
void			create_history_file(void);
void			write_history_file(char *read);

//builtins
int				echo_builtin(char **tokens);
int				pwd_builtin(void);
int				cd_builtin(char *command, t_vars *vars);
int				export_builtin(t_vars **head, char *var_name, char *var_value);
int				unset_builtin(t_vars **head, char *var_name);
int				exit_builtin(t_vars *vars, t_info *info);
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
void			signal_handler(int signal);
void			child_proc_handler(int signal);
void			heredoc_handler(int signal);
int				get_signal_received(void);
void			reset_signal(void);
void			heredoc_cleanup(int fd);
int				delim_found(int fd, char *read_input);
int				sim_press_hook(void);
void			init_heredoc(void);

//external commands
char			*find_path(t_vars *head, char *command);
int				exec_external_com(t_vars *head, char **cmd,
					int size, t_info *info);

//child process
int				create_child_proc(t_vars *vars, char **cmd, char *path,
					int size);
int				child_process(char *path, char **argv, char **env_copy);

//heredocs
//int				heredoc(t_info *info, char *delim);

//initializing
t_vars			*initialize_data(void);
t_info	*initialize_info(void);