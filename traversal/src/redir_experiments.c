/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_experiments.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rojornod <rojornod@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:20:49 by dloustal          #+#    #+#             */
/*   Updated: 2025/06/04 12:06:30 by rojornod         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "traversal.h"

// void execute_redir_out(ASTNode *node) {
//     if (!node || node->type != P_REDIR) return;

//     // Process the rightmost redirection first
//     if (node->right->type == P_REDIR) {
//         execute_redir_out(node->right);
//     } else {
//         char *filename = extract_filename(node->right);
//         int saved_stdout = dup(STDOUT_FILENO);
//         int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         if (fd < 0) {
//             perror("open");
//             return;
//         }
//         dup2(fd, STDOUT_FILENO);
//         close(fd);
//
//         // Recurse left
//         if (node->left->type == P_COMMAND) {
//             execute_command(node->left);
//         } else if (node->left->type == P_REDIR) {
//             execute_redir_out(node->left);
//         }
//
//         dup2(saved_stdout, STDOUT_FILENO);
//         close(saved_stdout);
//     }
// }

// void	exp_redir_out(t_t_node **root, t_vars *vars, t_shell_info *info)
// {
// 	int		fd;
// 	int		saved_stdout;
//	
// 	saved_stdout = dup(STDOUT_FILENO);
// 	if ((*root)->right->p_type == PARSER_REDIR && (*root)->right->tokens->head->token->type == TKN_REDIR_OUT)
// 	{
// 		if ((*root)->left->tokens->head->token->type == TKN_FILE_PATH)
// 		{
// 			fd = open((*root)->left->tokens->head->token->lexeme, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 			if (fd < 0)
// 			{
// 				ft_printf("open failed\n");
// 				close(fd);
// 				exit(EXIT_FAILURE);
// 			}
// 			if (dup2(fd, STDOUT_FILENO) < 0)
// 			{
// 				ft_printf("dup failed\n");
// 				close(fd);
// 				exit(EXIT_FAILURE);
// 			}
// 			close(fd);
// 		}
// 		exp_redir_out(&(*root)->right, vars, info);
// 	}
// 	else
// 	{
// 		fd = open((*root)->right->tokens->head->token->lexeme, O_WRONLY | O_TRUNC | O_CREAT, 0644);
// 		if (fd < 0)
// 		{
// 			ft_printf("open failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		ft_printf("{DEBUG} ====== before dup ====fd STDOUT: %d\n", STDOUT_FILENO);
// 		if (dup2(fd, STDOUT_FILENO) < 0)
// 		{
// 			ft_printf("dup failed\n");
// 			close(fd);
// 			exit(EXIT_FAILURE);
// 		}
// 		// ft_printf("{DEBUG} ====== after dup ====fd STDOUT: %d\n", STDOUT_FILENO);
// 		execute_command(&(*root)->left, vars, info);
// 		close(fd);
// 	}
// 	dup2(saved_stdout, STDOUT_FILENO);
// 	// ft_printf("{DEBUG} ====== after reseting with dup ====fd STDOUT: %d\n", STDOUT_FILENO);
//     close(saved_stdout);
// }

/********************************************************************************************
 * Assumming root->p_type == PARSER_REDIR
 ********************************************************************************************/
void	exp_redir_out(t_t_node **root, t_vars *vars, t_shell_info *info)
{
	if ((*root)->left->tokens->head->token->type == TKN_FILE_PATH)
	{
		ft_printf("My left child is a file name: %s\n",
			(*root)->left->tokens->head->token->lexeme);
	}
	if ((*root)->right->tokens->head->token->type == TKN_REDIR_OUT)
	{
		ft_printf("My right child is an out redir\n");
		exp_redir_out(&(*root)->right, vars, info);
	}
	else if ((*root)->right->tokens->head->token->type == TKN_FILE_PATH)
	{
		ft_printf("My right child is a file-path: %s\n",
			(*root)->right->tokens->head->token->lexeme);
	}
	if ((*root)->left->tokens->head->token->type != TKN_FILE_PATH)
	{
		ft_printf("And my left child is a command: %s\n",
			(*root)->left->tokens->head->token->lexeme);
	}
}
