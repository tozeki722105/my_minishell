/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _bool_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/14 02:02:09 by toshi             #+#    #+#             */
/*   Updated: 2024/03/08 02:44:18 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

t_bool is_ifs(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

t_bool is_quote(char c)
{
	return (c == '\"' || c == '\'');
}

t_bool is_delim(char c)
{
	return (is_ifs(c) || is_quote(c) || c == '<' || c == '>' \
		|| c == '$' || c == '|' || c == '\0');
}

t_bool is_valuable_tkn(enum e_token_kind kind)
{
	return (kind == TKN_TEXT || kind == TKN_S_QUOTE \
		|| kind == TKN_D_QUOTE || kind == TKN_ENV);
}

t_bool	is_in_redir_tkn(enum e_token_kind kind)
{
	return (kind == TKN_IN_FILE || kind == TKN_HEREDOC);
}

t_bool	is_out_redir_tkn(enum e_token_kind kind)
{
	return (kind == TKN_OUT_FILE || kind == TKN_APPEND_FILE);
}

t_bool	is_redir_tkn(enum e_token_kind kind)
{
	return (is_in_redir_tkn(kind) || is_out_redir_tkn(kind));
}

t_bool is_last_cmd(t_tree_node *ptr)
{
	return (ptr->right == NULL);
	//return (ptr->prev == NULL || ptr->prev->prev == NULL);
}

t_bool is_first_cmd(t_tree_node *ptr)
{
	return (ptr->left == NULL && (ptr->prev == NULL || ptr->prev->right != ptr));
}

t_bool	is_cmd_node(t_tree_node *ptr)
{
	return (ptr->refine_data.cmd_args || ptr->refine_data.infile_paths || ptr->refine_data.outfile_paths);
	//return (ptr->left == NULL && ptr->right == NULL); //木構造
}

t_bool	is_cmd_path(char *first_cmd_arg)
{
	return (ft_strchr(first_cmd_arg, '/') != 0);
}

t_bool	is_equal_str(const char *s1, char *s2)
{
	return (ft_strlen(s1) == ft_strlen(s2) && ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

t_bool	is_builtin(char *cmd)
{
	return (is_equal_str(cmd, "echo") || is_equal_str(cmd, "cd") || is_equal_str(cmd, "pwd") \
		|| is_equal_str(cmd, "export") || is_equal_str(cmd, "unset") || is_equal_str(cmd, "env") \
		|| is_equal_str(cmd, "exit"));
}