/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   token_list.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/03/18 12:09:34 by dloustal      #+#    #+#                 */
/*   Updated: 2025/04/02 16:14:36 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_token_list	*init_token_list(void)
{
	t_token_list	*list;

	list = malloc(sizeof(t_token_list));
	if (!list)
		return (NULL);
	list->head = NULL;
	return (list);
}

t_token	*create_token(enum e_Type type, char *lex)
{
	t_token	*token;
	char	*lexeme;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	lexeme = ft_strdup(lex);
	if (!lexeme)
		return (free(token), NULL);
	token->lexeme = lexeme;
	return (token);
}

t_token_node	*new_node(enum e_Type type, char *lex)
{
	t_token			*token;
	t_token_node	*node;

	if (!lex)
		return (NULL);
	token = create_token(type, lex);
	if (!token)
		return (NULL);
	node = malloc(sizeof(t_token_node));
	if (!node)
		return (free(token), NULL);
	node->token = token;
	node->next = NULL;
	return (node);
}

t_token_node	*get_last(t_token_list *list)
{
	t_token_node	*tmp;

	if (!list)
		return (NULL);
	tmp = list->head;
	if (!tmp)
		return (NULL);
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	append_token(t_token_list *list, enum e_Type type, char *lex)
{
	t_token_node	*last;
	t_token_node	*new;

	if (!list || !lex)
		return ;
	new = new_node(type, lex);
	if (!new)
		return ;
	if (!list->head)
		list->head = new;
	else
	{
		last = get_last(list);
		last->next = new;
	}
}

void	print_token_list(t_token_list *list)
{
	t_token_node	*node;

	if (!list)
		return ;
	node = list->head;
	if (!node)
		ft_printf("Token list is empty.\n");
	while (node)
	{
		printf("%d: %s\n", (node->token)->type, (node->token)->lexeme);
		node = node->next;
	}
}

t_scanner	*init_scanner(int cur, int start)
{
	t_scanner	*scanner;
	
	scanner = malloc(sizeof(t_scanner));
	if (!scanner)
		return (NULL);
	scanner->cur = cur;
	scanner->start = start;
	return (scanner);
}
