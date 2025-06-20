/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:53:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/21 18:31:06 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	tree_exec_clear(t_t_node *root, t_vars *vars, t_info *info)
{
	expand_var_tree(&root, vars, info);
	parse_hd_tree(&root, vars, info);
	execute_src(&root, vars, info);
	clear_subtree(root);
}

static void	scan_parse_exec(t_info *info, t_vars *vars, char *read)
{
	t_token_list	*tokens;
	t_t_node		*root;

	tokens = scan(read);
	if (!tokens)
	{
		info->exit_code = 2;
		clear_token_list(tokens);
		return ;
	}
	root = parse(tokens);
	clear_token_list(tokens);
	if (root == NULL)
	{
		info->exit_code = 2;
		free(root);
		return ;
	}
	tree_exec_clear(root, vars, info);
}

static void	handle_sigint_main(t_info *info)
{
	rl_done = 1;
	info->exit_code = 130;
	reset_signal();
}

int	main(int argc, char **argv, char **envp)
{
	t_vars			*vars;
	t_info			*info;
	char			*read;

	(void)argv;
	(void)argc;
	vars = initialize_data();
	info = initialize_info(vars, envp);
	while (1)
	{
		rl_done = 0;
		read = readline("> ");
		if (!read)
			exit_builtin(vars, info, info->exit_code);
		else if (get_signal_received() == SIGINT)
			handle_sigint_main(info);
		else if (read[0] == '\0')
			continue ;
		else
			scan_parse_exec(info, vars, read);
		add_history(read);
		free(read);
	}
	free_vars(vars);
	free(info);
}
