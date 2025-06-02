/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/06/02 16:53:17 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_vars	*initialize_data(void)
{
	t_vars	*head;

	head = malloc(sizeof(t_vars));
	if (!head)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	ft_memset(head, 0, sizeof(t_vars));
	return (head);
}

t_shell_info	*initialize_info(void)
{
	t_shell_info	*info;

	info = malloc(sizeof(t_shell_info));
	if (!info)
	{
		perror("malloc on vars initialization");
		exit(EXIT_FAILURE);
	}
	ft_memset(info, 0, sizeof(t_shell_info));
	info->fdin = dup(STDIN_FILENO);
	info->fdout = dup(STDOUT_FILENO);
	return (info);
}

char	*get_home_dir(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = NULL;
	if (!getcwd(buff, PATH_MAX + 1))
		return (NULL);
	current_directory = ft_strdup(buff);
	ft_printf("[current directory is %s]\n", current_directory);
	if (!current_directory)
		return (NULL);
	ft_printf("current directory is not null, returning current_directory\n");
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

	i = 0;
	fd = open("../.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	while (read[i] != '\0')
		i++;
	write(fd, read, i);
	write(fd, "\n", 1);
}

/******************************************************************************
*	
*	-This functon will copy all the environment variables given by the envp
*	 variable passed by the main();
*	-They are stored in the t_vars linked list;
*
******************************************************************************/
void	copy_env(t_vars **head, char **envp)
{
	int		i;
	char	**tokens;

	i = 0;
	while (envp[i])
	{
		tokens = ft_split(envp[i], '=');
		if (!tokens)
		{
			exit(EXIT_FAILURE);
		}
		else if (tokens && tokens[0] && tokens[1])
			add_var(head, tokens[0], tokens[1], 1);
		free_array(tokens);
		i++;
	}
}
