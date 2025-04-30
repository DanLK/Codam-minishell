/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:08 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/30 15:08:47 by rojornod         ###   ########.fr       */
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
#define STDIN  0
#define STDOUT 1

//parser stuff
enum e_Ptype
{
	PARSER_COMMAND,
	PARSER_PIPE,
	PARSER_REDIR,
	PARSER_FILEPATH
};
enum e_Type
{
	// Single character tokens
	TKN_L_PAREN, //0
	TKN_R_PAREN, //1
	TKN_EQUAL, //2
	// Builtins
	TKN_ECHO, //3
	TKN_CD,
	TKN_PWD, //5
	TKN_EXPORT,
	TKN_UNSET,
	TKN_ENV,
	TKN_EXIT, //9
	// Options
	TKN_OPTION,
	// Redirections
	TKN_REDIR_IN, //11
	TKN_REDIR_OUT,
	TKN_HEREDOC,
	TKN_REDIR_OUT_APP,
	// Operators
	TKN_PIPE, //15
	// Exit status ($?)
	TKN_EXIT_STATUS,
	// Parameter Expansion ($)
	TKN_ENV_VAR,
	// Path
	TKN_FILE_PATH, //18
	// Literals
	TKN_SQ_STRING,
	TKN_DQ_STRING,
	TKN_WORD, //21
	//EOF to indicate end of input
	TKN_END //22
};

typedef struct token
{
	enum e_Type	type;
	char		*lexeme;
}		t_token;

typedef struct s_token_node
{
	t_token				*token;
	struct s_token_node	*next;
}		t_token_node;

typedef struct s_token_list
{
	t_token_node	*head;
}		t_token_list;
typedef struct s_t_node
{
	t_token_list		*tokens;
	struct s_t_node		*left;
	struct s_t_node		*right;
	int					level;
	enum e_Ptype		p_type;
}		t_t_node;

// end parser stuff

typedef struct s_vars
{
	char				*name;
	char				*value;
	int					exported;
	int					hidden;
	struct s_vars		*next;
}	t_vars;

typedef struct s_fd_info
{
	int 	fdin;
	int 	fdout;
}	t_fd_info;

t_vars		*initialize_data(void);
t_fd_info	*initialize_info(void);

//directories
char	*get_home_dir(void);

//history
void	create_history_file(void);
void	write_history_file(char *read);

//builtins
void	echo_builtin(char **tokens);
void	pwd_builtin(void);
void	cd_builtin(char *command, t_vars *vars);
void	export_builtin(t_vars *head, char *var_name, char *var_value);
void	unset_builtin(t_vars **head, char *var_name);
void	exit_builtin(char *exit_cmd);
void	env_builtin(t_vars *head);

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
void	exec_external_com(t_vars *head, char **envp, char **cmd, int size);

//child process
int		create_child_proc(t_vars *vars, char **cmd, char *path, int size);

//pipes 
void	execute_pipe(t_t_node **node, t_vars *head);

//commands
int		is_builtin(char *command);
int		is_external_cmd(t_vars	*head, char *command);

