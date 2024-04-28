/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 17:07:30 by toshi             #+#    #+#             */
/*   Updated: 2024/04/28 09:11:02 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	print_init_data(t_tree_node *tree_node)
{
	printf("<<init_data>>\n");
	if (tree_node->init_data.cmd_tokens != NULL)
	{
		printf("<cmd>\n");
		print_token_list(tree_node->init_data.cmd_tokens);
	}
	if (tree_node->init_data.infile_tokens != NULL)
	{
		printf("<infile>\n");
		print_token_list(tree_node->init_data.infile_tokens);
	}
	if (tree_node->init_data.outfile_tokens != NULL)
	{
		printf("<outfile>\n");
		print_token_list(tree_node->init_data.outfile_tokens);
	}
}

void	print_adv_data(t_tree_node	*tree_node)
{
	printf("<<adv_data>>\n");
	if (tree_node->adv_data.cmd_args)
	{
		printf("<cmd>\n");
		print_cmd_args(tree_node->adv_data.cmd_args);
	}
	if (tree_node->adv_data.infile_paths)
	{
		printf("<infile>\n");
		print_redir_list(tree_node->adv_data.infile_paths);
	}
	if (tree_node->adv_data.outfile_paths)
	{
		printf("<outfile>\n");
		print_redir_list(tree_node->adv_data.outfile_paths);
	}
}

void	print_tree_node(t_tree_node *ptr)
{
	print_init_data(ptr);
	// print_adv_data(ptr);
}

/// @brief 木構造がちゃんと構成されているか、prevがちゃんとつながっているかのテスト
void	print_tree(t_tree_node *root)
{
	t_tree_node	*ptr;

	ptr = root;
	while (ptr->left != NULL)
	{
		print_tree_node(ptr);
		if (ptr->right)
			print_tree_node(ptr->right);
		ptr = ptr->left;
	}
	while (ptr != NULL)
	{
		print_tree_node(ptr);
		if (ptr->right != NULL)
			print_tree_node(ptr->right);
		ptr = ptr->prev;
	}
}
