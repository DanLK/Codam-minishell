/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   heredoc_parse_aux.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/06/17 16:22:48 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 18:12:56 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_file_name(t_info *info)
{
	char	*file_name;
	char	*index;

	index = ft_itoa(info->hd_count);
	file_name = ft_strjoin("/tmp/.tmp_heredoc", index);
	if (!file_name)
		return (NULL);
	free(index);
	return (file_name);
}

t_hd	*init_heredoc(t_info *info)
{
	char	*file_name;
	t_hd	*hd;

	file_name = get_file_name(info);
	if (!file_name)
		return (NULL);
	hd = malloc(sizeof(t_hd));
	if (!hd)
		return (NULL);
	hd->file_name = file_name;
	hd->input = NULL;
	hd->eof = NULL;
	hd->quoted_eof = false;
	hd->fd = 0;
	return (hd);
}

void	clear_hd_struct(t_hd *hd)
{
	if (!hd)
		return ;
	free(hd->input);
	free(hd->file_name);
	free(hd->eof);
	free(hd);
}

void	set_quoted_eof(t_hd *hd, t_redir_node *cur)
{
	if (cur->next->file[0] && (cur->next->file[0] == '"'
			|| cur->next->file[0] == '\''))
		hd->quoted_eof = true;
	else
		hd->quoted_eof = false;
}
