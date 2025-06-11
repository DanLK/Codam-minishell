/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:53:23 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/11 12:44:32 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

int	main(int argc, char **argv, char **envp)
{
	t_token_list	*tokens;
	t_t_node		*root;
	t_vars			*vars;
	t_info	*info;
	char			*home_dir;	
	char			*read;

	(void)argv;
	(void)argc;
	vars = initialize_data();
	info = initialize_info();
	copy_env(&vars, envp);
	home_dir = get_home_dir();
	edit_var(vars, "HOME", home_dir);
	rl_catch_signals = 0;
	signal_action();
	while (1)
	{
		rl_done = 0;
		read = readline("> ");
		if (!read)
		{
			free(home_dir);
			exit_builtin(vars, info);
		}	
		else if (get_signal_received() == SIGINT)
		{
			info->last_return_code = 130;
			reset_signal();
			free(read);
			continue ;
		}
		else if (read[0] == '\0')
			continue ;
		else
		{
			tokens = scan(read);
			if (tokens == NULL)
			{
				clear_token_list(tokens);
				continue ;
			}
			root = parse(tokens);
			if (root == NULL)
			{
				clear_token_list(tokens);
				free(root);
				continue ;
			}
			// ft_printf("-------------------------------------\n");
			// print_tree_node(root, "", 1);
			// ft_printf("-------------------------------------\n");
			expand_var_tree(&root, vars, info);
			parse_hd_tree(&root, vars, info);
			ft_printf("-------------------------------------\n");
			print_tree_node(root, "", 1);
			ft_printf("-------------------------------------\n");
			execute_src(&root, vars, info);
			clear_token_list(tokens);
			clear_subtree(root);
			// free(parser);
		}
		add_history(read);
		//write_history_file(read);
	}
	free_vars(vars);
	if (info->home_dir)
		free(info->home_dir);
	close(info->fdin);
	close(info->fdout);
	free(info);
	free(home_dir);
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