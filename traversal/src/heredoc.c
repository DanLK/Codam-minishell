/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:05:02 by rojornod          #+#    #+#             */
/*   Updated: 2025/05/20 17:10:28 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/traversal.h"

static int	sim_press_hook(void)
{
	if(get_signal_received() == SIGINT)
	{
		rl_replace_line("", 0);
		rl_done = 1;
	}
	return (0);
}
// static int	check_signal(int fd)
// {
// 	int		signal;
// 	signal = get_signal_received();
// 	if ( signal == 0)
// 		ft_printf("signal is 0\n");
// 	else
// 	{
// 		close(fd);
// 		unlink(".temp_heredoc");
// 		return (1);
// 	}
// 	return (0);
// }
	
/******************************************************************************
 *
 * 		Helper function for when the delimiter is reached.
 *		We reopne the file but in readonly mode and get next line will be 
	*	called until it returns null and every line will be printed to the standard output
	*	unlink will delete the file after it's not in use anymore
	*	
	******************************************************************************/
static int delim_found(int fd)
{
	char	*buf = NULL;
	
	ft_printf("[limiter found]\n");
	close(fd);
	fd = open(".temp_heredoc", O_RDONLY);
	while ((buf = get_next_line(fd)) != NULL)
	{
		ft_printf ("%s", buf);
		free(buf);
	}
	close(fd);
	unlink(".temp_heredoc");
	reset_signal();
	return (0);
}

/******************************************************************************
 *
 * 	This will be the main heredoc function. Once a heredoc is detected this will
 *	be called
	*
	******************************************************************************/
int heredoc(t_vars *vars, t_shell_info *info, char *delim)
{
	(void)vars;
	(void)info;
	(void)delim;
	int		fd;
	char 	*read_input;
	
	rl_catch_signals = 0;
	rl_event_hook = sim_press_hook;
	sim_press_hook();
	reset_signal();
	heredoc_action();
	fd = open(".temp_heredoc", O_WRONLY | O_APPEND | O_CREAT, 0644);
	read_input = readline("heredoc> ");
	if(get_signal_received() == SIGINT)
	{
		close(fd);
		unlink(".temp_heredoc");
		reset_signal();
		rl_done = 1;
		// rl_replace_line("", 0);
		// rl_on_new_line();
		// rl_redisplay();
		return (1);
	}
	while (read_input)
	{
		if (ft_strcmp(read_input, delim) == 0)
		{
			delim_found(fd);
			return (0);
		}
		write(fd, read_input, ft_strlen(read_input));
		write(fd,"\n",1);
		// free(read_input);
		read_input = readline("heredoc> ");
		if(get_signal_received() == SIGINT)
		{
			close(fd);
			unlink(".temp_heredoc");
			reset_signal();
			rl_done = 1;
			return (1);
		}
	}
	close(fd);
	return (0);
}


// int heredoc(t_vars *vars, t_shell_info *info, char *delim)
// {
// 	(void)vars;
// 	(void)info;
// 	(void)delim;
// 	int		fd;
// 	char 	*read_input;
// 	pid_t	pid;
// 	int		w_status;

	
// 	fd = open(".temp_heredoc", O_WRONLY | O_APPEND | O_CREAT, 0644);
// 	pid = fork();
// 	if (pid < 0)
// 		return(-1);
// 	else if (pid == 0)
// 	{
// 		rl_catch_signals = 0;
// 		reset_signal();
// 		heredoc_action();
// 		read_input = readline("heredoc> ");
// 		if(!read_input && get_signal_received() == SIGINT)
// 			return (1);
// 		while (read_input)
// 		{
// 			if (ft_strcmp(read_input, delim) == 0)
// 			{
// 				delim_found(fd);
// 				unlink(".temp_heredoc");
// 				reset_signal();
// 				return (0);
// 			}
// 			write(fd, read_input, ft_strlen(read_input));
// 			write(fd, "\n", 1);
// 			free(read_input);
// 			if (get_signal_received() == SIGINT)
// 				return (1);
// 			read_input = readline("heredoc> ");
// 			if(!read_input && get_signal_received() == SIGINT)
// 			{
// 				close(fd);
// 				unlink(".temp_heredoc");
// 				reset_signal();
// 				return (1);
// 			}
// 		}
// 		close(fd);
// 		return (0);
// 	}
// 	else
// 		waitpid(pid, &w_status, 0);
// 	return (0);
// }
