/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:53:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/05/14 17:15:15 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

int	main(int argc, char **argv, char **envp)
{
	t_token_list	*tokens;
	t_parser		*parser;
	t_t_node		*root;
	t_vars			*vars;
	t_shell_info	*info;
	char			*home_dir;	
	char			*read;
	(void)argv;
	(void)argc;
	
	
	vars = initialize_data();
	info = initialize_info();
	copy_env(&vars, envp);
	home_dir = get_home_dir();
	edit_var(vars, "HOME", home_dir);
	add_var(&vars, "TEST", NULL, 0);
	signal_action();

	while (1)
	{
		read = readline("> ");
		
		if (read[0] == '\0')
			continue ;
		else
		{
			tokens = scan(read);
			parser = malloc(sizeof(t_parser));
			if(!parser)
				return (0);
			parser->current = tokens->head;
			parser->previous = NULL;
			root = parse_pipe(parser);
			if (root == NULL)
			{
				clear_token_list(tokens);
				free(parser);
				exit(EXIT_FAILURE);
			}
			expand_var_tree(&root, vars, info);
			// ft_printf("-------------------------------------\n");
			// print_tree_node(root, "", 1);
			// ft_printf("-------------------------------------\n");
			execute_src(&root, vars, info);
			clear_token_list(tokens);
			clear_subtree(root);
			free(parser);
		}
		add_history(read);
		//write_history_file(read);
	}
}

// int	main(int argc, char **argv, char **envp)
// {
// 	t_token_list	*tokens;
// 	t_parser		*parser;
// 	t_t_node		*root;
// 	t_vars			*vars;
// 	char			*home_dir;
// 	(void)argc;
// 	(void)argv;

// 	vars = initialize_data();
// 	copy_env(&vars, envp);
// 	home_dir = get_home_dir();
// 	edit_var(vars, "HOME", home_dir);
// 	add_var(&vars, "TEST", NULL, 0);

// 	tokens = scan("MYVAR=$PWD");
// 	// print_token_list(tokens);
// 	// ft_printf("-------------------------------------\n");
// 	parser = malloc(sizeof(t_parser));
// 	if(!parser)
// 		return (0);
// 	parser->current = tokens->head;
// 	parser->previous = NULL;
// 	root = parse_pipe(parser);
// 	// print_tree_node(root, "", 1);
// 	// ft_printf("-------------------------------------\n");
// 	expand_var_tree(&root, vars);
// 	print_tree_node(root, "", 1);
// 	clear_token_list(tokens);
// 	clear_subtree(root);
// 	free(parser);
// }