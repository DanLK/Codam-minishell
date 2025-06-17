/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dloustal <dloustal@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/04/17 11:53:23 by dloustal      #+#    #+#                 */
/*   Updated: 2025/06/17 12:20:52 by dloustal      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_token_list	*tokens;
	t_t_node		*root;
	t_vars			*vars;
	t_info			*info;
	char			*read;

	(void)argv;
	(void)argc;
	vars = initialize_data();
	info = initialize_info();
	copy_env(&vars, envp);
	rl_catch_signals = 0;
	signal_action();
	while (1)
	{
		rl_done = 0;
		read = readline("> ");
		if (!read)
			exit_builtin(vars, info, info->last_return_code);
		else if (get_signal_received() == SIGINT)
		{
			rl_done = 1;
			info->last_return_code = 130;
			reset_signal();
		}
		else if (read[0] == '\0')
			continue ;
		else
		{
			tokens = scan(read);
			if (tokens == NULL)
			{
				info->last_return_code = 2;
				clear_token_list(tokens);
				continue ;
			}
			root = parse(tokens);
			if (root == NULL)
			{
				info->last_return_code = 2;
				clear_token_list(tokens);
				free(root);
				continue ;
			}
			expand_var_tree(&root, vars, info);
			parse_hd_tree(&root, vars, info);
			execute_src(&root, vars, info);
			clear_token_list(tokens);
			clear_subtree(root);
		}
		add_history(read);
	}
	free_vars(vars);
	close(info->fdin);
	close(info->fdout);
	free(info);
}
