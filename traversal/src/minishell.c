/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:53:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/22 11:00:26 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*home_dir;	
	char	*read;
	t_vars	*vars;
	
	argc = 0;
	(void)argv;
	vars = initialize_data();
	// extra = initialize_extra();
	debug_print("initializing environment", 'd');
	copy_env(&vars, envp);
	debug_print("environment copied", 'd');
	debug_print("env\n", 'd');
	debug_print("getting home directory", 'd');
	home_dir = get_home_dir();
	edit_var(vars, "HOME", home_dir);
	add_var(&vars, "TEST", NULL, 0);
	create_history_file();
	signal_action();
	while (1)
	{
		read = readline("> ");
		
		if (read[0] == '\0')
			continue ;
		
		else if (ft_strcmp(read, "pwd") == 0)
			pwd_builtin();
			
		else if (ft_strncmp(read, "echo", 4) == 0)
			echo_builtin(read);
		
		else if (ft_strcmp(read, "cd") == 0)
			cd_builtin("execution", vars);
		
		else if (ft_strcmp(read, "cd2") == 0)
			cd_builtin(NULL, vars);

		else if (ft_strcmp(read, "cd3") == 0)
			cd_builtin("..", vars);

		else if (ft_strcmp(read, "cd4") == 0)
			cd_builtin("sources", vars);
			
		else if (ft_strcmp(read, "edit") == 0) //edits variable with name HOME to a custom value
			edit_var(vars, "HOME", "rojornod/personal/minishell/execution");
			
		else if (ft_strcmp(read, "env") == 0) //env with no arguments displays the list of environment variables
			env_builtin(vars);
			
		else if (ft_strcmp(read, "export") == 0) //export with no arguments. displays the list of all exported variables
			export_builtin(vars, NULL, NULL);
			
		else if (ft_strcmp(read, "export2") == 0) //exports TEST2 with value exmple
			export_builtin(vars, "TEST2", "example");

		else if (ft_strcmp(read, "export3") == 0) //exports TEST3 with no value
			export_builtin(vars, "TEST3", NULL);
			
		else if (ft_strcmp(read, "unset") == 0) //deletes the variable with name LC_NUMERIC
			unset_builtin(&vars, "LC_NUMERIC");
			
		else if (ft_strcmp(read, "unset2") == 0) //deletes the variable with name TERM_PROGRAM
			unset_builtin(&vars, "TERM_PROGRAM");
			
		else if (ft_strcmp(read, "unset3") == 0) //deletes the variable with nme TEST
			unset_builtin(&vars, "TEST");
			
		else if (ft_strcmp(read, "minishell") == 0) //opens a new minishell inside a minishell using child processes
			{
			char **command;
			
			command = ft_split(read, ' ');
			int i = 0;
			while (command[i])
			{
				ft_printf("[%d] [%s]\n", i, command[i]);
				i++;
			}
			create_child_proc(vars, command, "./minishell", i);
		}	
		else if (ft_strcmp(read, "envlist") == 0) //converts the environment variables from a linked list to an array then displays it 
			convert_env(vars);
		
		else if (ft_strcmp(read, "pid") == 0) //shows the pid of the current process
			show_pid();
		
		else if (ft_strcmp(read, "find") == 0) //tries to find the variable with name HOME 
			find_vars(vars, "HOME");
		
		else if (ft_strncmp(read, "find", 4) == 0) //tries to find a variable you given the name. syntax: find <variable name>
		{
			int 	i = 5;
			int		j = 0;
			int		size;
			char	*var_name;
			
			size = (ft_strlen(read)- 5);
			var_name = malloc(size * (sizeof(char)));
			while (read[i] != '\0')
			var_name[j++] = read[i++];	  
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
			char **command;
			
			//ft_printf("command is else\n");
			command = ft_split(read, ' ');
			if (!command)
			ft_printf("command array is null\n");
			int i = 0;
			while (command[i])
			{
				//ft_printf("[%d] [%s]\n", i, command[i]);
				i++;
			}
			exec_external_com(vars, envp, command, i);
			// if (ft_strcmp(read, "date") == 0)
			// 	exec_external_com(vars, envp, read);
			
			// if (ft_strcmp(read, "ls") == 0)
			// 	exec_external_com(vars, envp, read);
			
			// if (ft_strcmp(read, "whoami") == 0)
			// 	exec_external_com(vars, envp, read);
			
			// if (ft_strcmp(read, "uptime") == 0)
			// 	exec_external_com(vars, envp, read);
			
			// if (ft_strcmp(read, "hostname") == 0)
			// 	exec_external_com(vars, envp, read);
			
			// if (ft_strcmp(read, "invalidcom") == 0)
			// 	exec_external_com(vars, envp, read);
			
			// if (ft_strcmp(read, "mkdir") == 0)
			// 	exec_external_com(vars, envp, read);
		}
			
			/***************************************/
		add_history(read);
		write_history_file(read);
	}
	return (0);
}