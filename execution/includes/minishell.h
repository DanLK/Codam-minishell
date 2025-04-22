/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/10 14:21:08 by rojornod      #+#    #+#                 */
/*   Updated: 2025/04/22 16:44:59 by dloustal      ########   odam.nl         */
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
#include "../../libft/libft.h"

typedef struct s_vars
{
	char				*name;
	char				*value;
	int					exported;
	int					hidden;
	struct s_vars		*next;
}	t_vars;
typedef struct s_pipe_info
{
	int fdin;
	int fdout;
}	t_info;

// typedef struct	s_extra
// {
// 	bool	ischild;
// 	pid_t	childpid;

// }	t_extra;

t_vars	*initialize_data(void);

//directories
char	*get_home_dir(void);

//history
void	create_history_file(void);
void	write_history_file(char *read);

//builtins
void	echo_builtin(char *string);
void	pwd_builtin(void);
void	cd_builtin(char *command, t_vars *vars);
void	export_builtin(t_vars *head, char *var_name, char *var_value);
void	unset_builtin(t_vars **head, char *var_name);
void	exit_builtin(char *exit_cmd);

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

//external commands
char	*find_path(t_vars *head, char *command);
void	exec_external_com(t_vars *head, char **envp, char **command, int size);

//child process
int		create_child_proc(t_vars *vars, char **command, char *path, int size);


//commands
int	is_builtin(char *command);
int	is_external_cmd(t_vars	*head, char *command);
