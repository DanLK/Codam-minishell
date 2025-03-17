/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:21:17 by rojornod          #+#    #+#             */
/*   Updated: 2025/03/17 15:25:41 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	-Creates the file .shell_history which will store all 
	commands typed by user
	
	-The file is created in the root directory
*/
void	create_history_file(void)
{
	int	fd;

	fd = open("./.shell_history", O_WRONLY | O_APPEND | O_CREAT, 0644);
	printf("file created\n");
	close(fd);
}

/*
	-This function takes the input from the command line and appends it to the 
	.shell_history file
*/
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

/*
	-Currently this function simply displays the current working directory if 
	it detects that the user typed pwd
	
	-getcwd gives you the current working directory when given a buffer and 
	size
*/
void	get_current_directory(void)
{
	char	*current_directory;
	char	buff[PATH_MAX + 1];

	current_directory = getcwd(buff, PATH_MAX + 1);
	if (current_directory != NULL)
		ft_printf("%s\n", current_directory);
}

/*
	-The main maintains a constant loop until terminated by user.
	
	-It simulates and actual shell, where you can keep inputing commands
*/
int	main(void)
{
	char	*read;

	create_history_file();
	while (1)
	{
		read = readline("> ");
		add_history(read);
		if (ft_strncmp(read, "pwd", 3) == 0)
			get_current_directory();
		write_history_file(read);
	}
	return (0);
}
