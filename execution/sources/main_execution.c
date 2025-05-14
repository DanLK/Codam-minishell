/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:20:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/14 17:14:49 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/******************************************************************************
*
*	-The main maintains a constant loop until terminated by user.
*
*	-It simulates and actual shell, where you can keep inputing commands
*
******************************************************************************/
int	main(int argc, char **argv, char **envp)
{
	char		*read;
	t_vars		*vars;
	t_shell_info 	*info;
	(void)argv;
	(void)argc;
	
	vars = initialize_data();
	info = initialize_info();
	// extra = initialize_extra();
	debug_print("initializing environment", 'r');
	copy_env(&vars, envp);
	debug_print("environment copied", 'r');
	debug_print("env", 'r');
	debug_print("getting home directory", 'r');
	info->home_dir = get_home_dir();
	edit_var(vars, "HOME", info->home_dir);
	add_var(&vars, "TEST", "val", 0);
	add_var(&vars, "TEST3", "val3", 0);
	create_history_file();
	// if (info->is_child_running == 0)
	// 	signal_action();
	// else
	// {
	// 	debug_print("there is a child running", 'r');
	// 	child_signal_action();
	// }	
	while (1)
	{
		read = readline("> ");
		
		if (read[0] == '\0')
			continue ;
		
		else if (ft_strchr(read, '|'))
		{
			char **command;
			
			command = ft_split(read, '|');
			if (!command)
				ft_printf("command array is null\n");
			int i = 0;
			while (command[i])
				i++;
			//execute_pipe(vars, info, envp, command);
		}
		
		else if (ft_strcmp(read, "heredoc"))
			heredoc(vars, info, "eof");
		
			else if (ft_strcmp(read, "pwd") == 0)
		{
			debug_print("command is pwd", 'r');
			// is_external_cmd(vars, read);
			// is_builtin(read);
			pwd_builtin();
		}	
		else if (ft_strncmp(read, "echo", 4) == 0)
		{
			char **tokens;

			tokens = ft_split(read, ' ');
			if (!tokens)
				return (-1);
			echo_builtin(tokens);
		}
		
		else if (ft_strcmp(read, "cd") == 0)
			cd_builtin("execution", vars);
		
		else if (ft_strcmp(read, "cd2") == 0)
			cd_builtin(NULL, vars);

		else if (ft_strcmp(read, "cd3") == 0)
			cd_builtin("..", vars);

		else if (ft_strcmp(read, "cd4") == 0)
			cd_builtin("sources", vars);
		
		else if (ft_strcmp(read, "exit") == 0)
			exit_builtin(vars, info);
			
		else if (ft_strcmp(read, "edit") == 0) //edits variable with name HOME to a custom value
			edit_var(vars, "HOME", "rojornod/personal/minishell/execution");
			
		else if (ft_strcmp(read, "env") == 0) //env with no arguments displays the list of environment variables
			env_builtin(vars);
			
		else if (ft_strcmp(read, "export") == 0) //export with no arguments. displays the list of all exported variables
			export_builtin(&vars, NULL, NULL);
			
		else if (ft_strcmp(read, "export2") == 0) //exports TEST2 with value exmple
			export_builtin(&vars, "TEST2", "example");

		else if (ft_strcmp(read, "export3") == 0) //exports TEST3 with no value
			export_builtin(&vars, "TEST3", NULL);
			
		else if (ft_strcmp(read, "unset") == 0) //deletes the variable with name LC_NUMERIC
			unset_builtin(vars, "LC_NUMERIC");
			
		else if (ft_strcmp(read, "unset2") == 0) //deletes the variable with name TERM_PROGRAM
			unset_builtin(vars, "TERM_PROGRAM");
			
		else if (ft_strcmp(read, "unset3") == 0) //deletes the variable with nme TEST
			unset_builtin(vars, "TEST");
			
		else if (ft_strcmp(read, "minishell") == 0) //opens a new minishell inside a minishell using child processes
		{
			char	**cmd;
			
			cmd = ft_split(read, ' ');
			int i = 0;
			while (cmd[i])
			{
				ft_printf("[%d] [%s]\n", i, cmd[i]);
				i++;
			}
			create_child_proc(vars, cmd, "./minishell", i, info);
		}	
		else if (ft_strcmp(read, "envlist") == 0) //converts the environment variables from a linked list to an array then displays it 
			convert_env(vars);
		
		else if (ft_strcmp(read, "pid") == 0) //shows the pid of the current process
			show_pid();
		
		else if (ft_strcmp(read, "find") == 0) //tries to find the variable with name HOME 
			find_vars(vars, "exit_code");
		
		else if (ft_strncmp(read, "find", 4) == 0) //tries to find a variable you given the name. syntax: find <variable name>
		{
			int 	i = 5;
			int		j = 0;
			int		size;
			char	*var_name;
			
			size = (ft_strlen(read) - 5);
			var_name = malloc(size * (sizeof(char)) + 1);
			while (read[i] != '\0')
				var_name[j++] = read[i++];
			var_name[j] = '\0';
			find_vars(vars, var_name);
			
		}
		/* 
		- 	If command is not one of the hard coded ones it means its one of the external ones.
		- 	That will trigger the else branch where the command will be split into tokens and 
		sent to the exec_external_com function that will try to find the command path in the
		PATH variable. 
		- 	If the command is found a child process will be created to run the command with any 
		flag or other atributes.
		
		
		*/
		/**********external commands************/
		else 
		{
			char **cmd;	
				
			debug_print("external command", 'r');
			cmd = ft_split(read, ' ');
			if (!cmd)
				ft_printf("command array is null\n");
			int i = 0;
			while (cmd[i])
				i++;
			debug_print("checks made om external commands", 'r');
			exec_external_com(vars, cmd, i, info);
		}
		add_history(read);
		write_history_file(read);
	}
	return (0);
}
