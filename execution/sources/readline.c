/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/04/08 17:03:56 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*initialize_data(void)
{
	t_vars	*vars;

	vars = malloc(sizeof(t_vars));
	if (!vars)
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
	ft_printf("assigned directory\n");
	ft_printf("exiting functions...\n");
	ft_printf("cd is %s\n", current_directory);
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
	printf("history file created\n");
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
	int	fd;
	int	i;

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

int	create_child_proc(t_vars *vars)
{
	pid_t	pid;
	
	char	*argv[] = {"minishell", NULL};
	char 	**env_copy;
	
	ft_printf("converting environment...\n");
	env_copy = convert_env(vars);
	ft_printf("environment converted\n");
	int i = 0;
	while (!env_copy)
	{
		
		ft_printf("%s\n", env_copy[i]);
		i++;
	}
	ft_printf("variables copied...\n");
	pid = fork();
	if (pid == 0)
	{
		ft_printf("Parent PID: [%d]\nChild PID: [%d]\n", getppid(), getpid());
		//exit(EXIT_SUCCESS);
	}
	else if (pid > 0)
	{
		ft_printf("Parent PID: [%d]\n", getpid());
		ft_printf("Waiting for child to finish\n");
		while(1)
			wait(NULL);
		ft_printf("child process finished\n");
	}
	else
	{
		ft_printf("Error creating child process\n");
		return (1);	
	}
	execve("./minishell", argv, env_copy);
	return (EXIT_SUCCESS);
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

	ft_printf("initializing_data..\n");
	vars = initialize_data();
	ft_printf("copying environment..\n");
	copy_env(&vars, envp);
	ft_printf("environment_copied..\n");
	home_dir = get_home_dir();
	edit_var(vars, "HOME", home_dir);
	add_var(&vars, "TEST", NULL, 0);
	create_history_file();
	ft_printf("created history file\n");
	signal_action();
	while (1)
	{
		read = readline("> ");
		add_history(read);
		if (ft_strcmp(read, "pwd") == 0)
			pwd_builtin();
			
		if (ft_strncmp(read, "echo", 4) == 0)
			echo_builtin(read);
			
		if (ft_strcmp(read, "cd") == 0)
			cd_builtin("execution", vars);
			
		if (ft_strcmp(read, "cd2") == 0)
			cd_builtin(NULL, vars);

		if (ft_strcmp(read, "cd3") == 0)
			cd_builtin("..", vars);

		if (ft_strcmp(read, "cd4") == 0)
			cd_builtin("sources", vars);
			
		if (ft_strcmp(read, "edit") == 0) //edits variable with name HOME to a custom value
			edit_var(vars, "HOME", "rojornod/personal/minishell/execution");
			
		if (ft_strcmp(read, "env") == 0) //env with no arguments displays the list of environment variables
			env_builtin(vars);
						
		if (ft_strcmp(read, "export") == 0) //export with no arguments. displays the list of all exported variables
			export_builtin(vars, NULL, NULL);
			
		if (ft_strcmp(read, "export2") == 0) //exports TEST2 with value exmple
			export_builtin(vars, "TEST2", "example");

		if (ft_strcmp(read, "export3") == 0) //exports TEST3 with no value
			export_builtin(vars, "TEST3", NULL);
			
		if (ft_strcmp(read, "unset") == 0) //deletes the variable with name LC_NUMERIC
			unset_builtin(&vars, "LC_NUMERIC");
			
		if (ft_strcmp(read, "unset2") == 0) //deletes the variable with name TERM_PROGRAM
			unset_builtin(&vars, "TERM_PROGRAM");
			
		if (ft_strcmp(read, "unset3") == 0) //deletes the variable with nme TEST
			unset_builtin(&vars, "TEST");
			
		if (ft_strcmp(read, "minishell") == 0) //opens a new minishell inside a minishell using child processes
			create_child_proc(vars);
			
		if (ft_strcmp(read, "envlist") == 0) //converts the environment variables from a linked list to an array then displays it 
			convert_env(vars);
			
		if (ft_strcmp(read, "pid") == 0) //shows the pid of the current process
			show_pid();

		if (ft_strcmp(read, "find") == 0) //tries to find the variable with name HOME 
			find_vars(vars, "HOME");
			
		if (ft_strncmp(read, "find", 4) == 0) //tries to find a variable you given the name. syntax: find <variable name>
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
		write_history_file(read);
	}
	return (0);
}
