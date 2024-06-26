/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 16:36:24 by username          #+#    #+#             */
/*   Updated: 2024/05/03 17:34:43 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "../minishell.h"

enum e_mode
{
	MODE_FIRST,
	MODE_PIPE,
	MODE_REDIR,
};

t_tree_node	*parse(t_token *tkn_head);
t_bool		validate_syntax(t_token *ptr);
void		move_to_redir_tokens(t_tree_node *ptr);

#endif
