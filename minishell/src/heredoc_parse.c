/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parse.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/17 17:58:53 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 18:11:59 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*******************************************************************************
 * Returns an int that corresponds to the event:
 * 
 * 0 if SIGINT was received
 * 1 if !input (Ctrl + D)
 * 2 if input == eof
 * 3 else
*******************************************************************************/
static int	catch_input(t_redir_node *cur, t_vars *vars, t_info *info, t_hd *hd)
{
	char	*old_file;

	if (hd->quoted_eof)
		hd->input = readline("heredoc> ");
	else
		hd->input = expand_qstring(readline("heredoc> "), vars, info);
	if (get_signal_received() == SIGINT)
	{
		old_file = cur->next->file;
		cur->next->file = ft_strdup(hd->file_name);
		return (free(old_file), info->hd_count++, heredoc_cleanup(*hd->fd), 0);
	}
	if (!hd->input)
	{
		old_file = cur->next->file;
		cur->next->file = ft_strdup(hd->file_name);
		return (free(old_file), info->hd_count++, 1);
	}
	if (ft_strcmp(hd->input, hd->eof) == 0)
	{
		old_file = cur->next->file;
		cur->next->file = ft_strdup(hd->file_name);
		return (free(old_file), close(*hd->fd), info->hd_count++, 2);
	}
	return (3);
}

static void	write_and_clear(t_hd *hd)
{
	write(*hd->fd, hd->input, ft_strlen(hd->input));
	write(*hd->fd, "\n", 1);
	free(hd->input);
}

/*******************************************************************************
 * Creates the heredoc prompt and does the reading, creating file and 
 * parsing the input
 * 
 * It stops when it hits the specified eof string
*******************************************************************************/
void	parse_hd(t_redir_node *cur, t_vars *vars, t_info *info)
{
	int		fd;
	t_hd	*hd;
	int		event;

	init_sig_heredoc();
	sim_press_hook();
	heredoc_action();
	hd = init_heredoc(info);
	if (!hd)
		return ;
	fd = open(hd->file_name, O_WRONLY | O_CREAT, 0644);
	hd->fd = &fd;
	if (fd < 0)
		return (clear_hd_struct(hd));
	hd->eof = remove_quotes(cur->next->file);
	set_quoted_eof(hd, cur);
	while (1)
	{
		event = catch_input(cur, vars, info, hd);
		if (event == 0)
			return (sigint_clean(*hd->fd, hd->file_name), clear_hd_struct(hd));
		if (event == 1 || event == 2)
			return (heredoc_cleanup(*hd->fd), clear_hd_struct(hd));
		write_and_clear(hd);
	}
}
