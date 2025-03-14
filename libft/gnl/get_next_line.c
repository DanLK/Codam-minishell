/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/12/26 19:17:57 by dloustalot    #+#    #+#                 */
/*   Updated: 2025/01/03 11:21:01 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>

void	read_to_list(int fd, t_list **list);
char	*get_current_line(t_list *head);
void	copy_line(t_list *head, char *line);
void	set_list(t_list **list);

char	*get_next_line(int fd)
{
	static t_list	*stash = NULL;
	char			*line;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	read_to_list(fd, &stash);
	if (!stash)
		return (NULL);
	line = get_current_line(stash);
	if (line == NULL)
		return (clear_list(&stash, NULL, NULL), NULL);
	set_list(&stash);
	return (line);
}

/* Reads content until a new line and stores in stash */
void	read_to_list(int fd, t_list **list)
{
	ssize_t		result;
	t_list		*new_node;
	char		*buffer;

	if (list == NULL)
		return ;
	while (!find_new_line(*list, 'f'))
	{
		buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buffer)
			return (clear_list(list, NULL, NULL));
		result = read(fd, buffer, BUFFER_SIZE);
		if (result <= 0)
		{
			free(buffer);
			if (result < 0)
				clear_list(list, NULL, NULL);
			return ;
		}
		buffer[result] = '\0';
		new_node = ft_lstnew(buffer);
		if (!new_node)
			return (clear_list(list, NULL, buffer));
		ft_lstadd_back(list, new_node);
	}
}

/* Reads stash and gets the first line */
char	*get_current_line(t_list *head)
{
	char	*line;
	int		line_len;

	if (!head)
		return (NULL);
	line_len = find_new_line(head, 'c');
	line = (char *)malloc((line_len + 1) * sizeof(char));
	if (!line)
		return (NULL);
	copy_line(head, line);
	return (line);
}

void	copy_line(t_list *head, char *line)
{
	int	i;
	int	j;

	if (!head || !line)
		return ;
	i = 0;
	while (head)
	{
		j = 0;
		while (head->content[j])
		{
			line[i++] = head->content[j];
			if (head->content[j] == '\n')
			{
				line[i] = '\0';
				return ;
			}
			j++;
		}
		head = head->next;
	}
	line[i] = '\0';
}

/* Sets the stash for next iteration */
void	set_list(t_list **list)
{
	t_list	*new_node;
	t_list	*last_node;
	char	*content;
	int		i;
	int		j;

	new_node = (t_list *)malloc(sizeof(t_list));
	content = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!new_node || !content)
		return (free(new_node), free(content), clear_list(list, NULL, NULL));
	last_node = ft_lstlast(*list);
	i = 0;
	j = 0;
	while (last_node->content[i] && last_node->content[i] != '\n')
		i++;
	if (last_node->content[i] == '\n')
		i++;
	while (last_node->content[i])
		content[j++] = last_node->content[i++];
	content[j] = '\0';
	new_node->content = content;
	new_node->next = NULL;
	clear_list(list, new_node, content);
}
