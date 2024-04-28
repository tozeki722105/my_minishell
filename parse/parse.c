/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 21:28:02 by toshi             #+#    #+#             */
/*   Updated: 2024/04/28 09:07:02 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static t_token	*search_last_pipe(t_token* ptr)
{
	t_token *last_pipe;

	last_pipe = NULL;
	while (ptr != NULL)
	{
		if (ptr->kind == TKN_PIPE)
			last_pipe = ptr;
		ptr = ptr->next;
	}
	return (last_pipe);
}

static t_tree_node	*make_new_tree(t_token *first, t_token *last)
{
	t_tree_node *new;

	new = (t_tree_node *)ft_xcalloc(1, sizeof(t_tree_node));
	new->init_data.cmd_tokens = first;
	if (last)
		last->next = NULL;
	return (new);
}

//最低1つはpipeノードの存在が保証されている前提で実装している
//pipeノードの前には最低1つ何かしらのノードがあること(syntax_errでない)前提で実装している
static t_tree_node *make_tree_list(t_token *tkn_head, t_tree_node *pipe_node_prev)
{
	t_tree_node	*right_node;
	t_tree_node	*pipe_node;
	t_tree_node	*left_node;
	t_token		*last_pipe;

	last_pipe = search_last_pipe(tkn_head);
	search_prev_token(tkn_head, last_pipe)->next = NULL;
	right_node = make_new_tree(last_pipe->next, NULL);
	pipe_node = make_new_tree(last_pipe, last_pipe);
	right_node->prev = pipe_node;
	pipe_node->right = right_node;
	pipe_node->prev = pipe_node_prev;
	last_pipe = search_last_pipe(tkn_head);
	if (!last_pipe)
	{
		left_node = make_new_tree(tkn_head, NULL);
		left_node->prev = pipe_node;
		pipe_node->left = left_node;
		return (pipe_node);
	}
	pipe_node->left = make_tree_list(tkn_head, pipe_node);
	return (pipe_node);
}

t_tree_node *parse(t_token *tkn_head)
{
	t_token *pipe;
	
	if (!validate_syntax(tkn_head))
	{
		free_token_list(tkn_head);
		return (NULL);	
	}
	pipe = search_last_pipe(tkn_head);
	if (!pipe)
		return (make_new_tree(tkn_head, NULL));
	return (make_tree_list(tkn_head, NULL));
}