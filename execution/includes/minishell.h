/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:08 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/05 16:36:22 by rojornod         ###   ########.fr       */
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
	bool	is_child_running;
	int		last_return_code;
	int		**child_pid;
	int 	fdin;
	int 	fdout;
}	t_shell_info;

t_vars			*initialize_data(void);
t_shell_info	*initialize_info(void);

//directories
char	*get_home_dir(void);

//history
void	create_history_file(void);
void	write_history_file(char *read);

//builtins
int	echo_builtin(char **tokens);
int	pwd_builtin(void);
int	cd_builtin(char *command, t_vars *vars);
int	export_builtin(t_vars *head, char *var_name, char *var_value);
int	unset_builtin(t_vars **head, char *var_name);
int	exit_builtin(void);
int	env_builtin(t_vars *head);

//variables
t_vars	*add_var(t_vars **head, char *var_name, char *var_value, int exp);
t_vars	*create_var(char *name, char *value, int exp);
t_vars	*find_vars(t_vars *head, char *var_name);
void	copy_env(t_vars **head, char **envp);
void	edit_var(t_vars *vars, char *var_name, char *var_value);

//utils
int		ft_strcmp(char *s1, char *s2);
void	free_array(char **array);
void	show_pid(void);
char	**convert_env(t_vars *head);
void	debug_print(char *debug_message, char c);

//signals
void	signal_action(void);
void	child_signal_action(void);

//external commands
char	*find_path(t_vars *head, char *command);
void	exec_external_com(t_vars *head, char **cmd, int size, t_shell_info *info);

//child process
int		create_child_proc(t_vars *vars, char **cmd, char *path, int size, t_shell_info *info);

//pipes 
int		execute_pipe(t_t_node **node, t_vars *head);

//commands
int		is_builtin(char *command);
int		is_external_cmd(t_vars	*head, char *command);

//return values
int return_codes(t_shell_info	*info, int return_code);

