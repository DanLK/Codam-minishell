/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/16 15:43:22 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// t_vars	initialize_data(void)
// {
// 	t_vars *head;
// 	ft_printf("initializing date\n");
// 	// head = malloc(sizeof(t_vars));
// 	// if (!head)
// 	// {
// 	// 	perror("malloc on vars initialization");
// 	// 	exit(EXIT_FAILURE);
// 	// }
// 	head->name = NULL;
// 	head->value = NULL;
// 	head->exported = 0;
// 	head->hidden = 0;
// 	head->next = NULL;
// 	ft_printf("date initialized");
// 	return (NULL);
// }

t_vars	*initialize_data(void)
{
	t_vars	*head;
	debug_print("initializing extra");

	head = malloc(sizeof(t_vars));
	debug_print("malloced struct");
	if (!head)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	return (NULL);
}

static char	*get_home_dir(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = NULL;
	if (!getcwd(buff, PATH_MAX + 1))
		return (NULL);
	current_directory = ft_strdup(buff);
	// ft_printf("assigned directory\n");
	// ft_printf("exiting functions...\n");
	// ft_printf("cd is %s\n", current_directory);
	return (current_directory);
}

/******************************************************************************
*
*	-Creates the file .shell_history which will store all 
*	commands typed by user
*	
*	-The file is created in the root directory
*	
******************************************************************************/
void	create_history_file(void)
{
	int	fd;

	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	// ft_printf("history file created\n");
	close(fd);
}

/******************************************************************************
*
*	-This function takes the input from the command line and appends it to the 
*	.shell_history file
*	
******************************************************************************/
void	write_history_file(char *read)
{
	int		fd;
	int		i;
	char	*number;
	
	i = 0;
	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (read[i] != '\0')
		i++;
	write(fd, read, i);
	write(fd, "\n", 1);
}

void	print_environment(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		ft_printf("%s\n", envp[i]);
		i++;
	}
}



/******************************************************************************
*
*	-The main maintains a constant loop until terminated by user.
*
*	-It simulates and actual shell, where you can keep inputing commands
*
******************************************************************************/
int	main(int argc, char **argv, char **envp)
{
	char	*home_dir;	
	char	*read;
	t_vars	*vars;
	
	
	vars = initialize_data();
	// extra = initialize_extra();
	debug_print("initializing environment");
	copy_env(&vars, envp);
	debug_print("environment copied");
	debug_print("env\n");
	debug_print("getting home directory");
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
