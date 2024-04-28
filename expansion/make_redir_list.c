/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_redir_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 20:56:07 by toshi             #+#    #+#             */
/*   Updated: 2024/04/28 09:08:28 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../minishell.h"
#include "../utils/utils.h"
#include "../libft/libft.h"

static t_redir	*find_last_redir(t_redir *ptr)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static void	add_redir_last(t_redir **head, t_redir *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_redir(*head)->next = new;
}

//リダイレクトのvalがifsのみだと、空文字列("")が入る
//意図した通りにtirmするならsubstr_from_token前に前後のスペースtokenは消す、
//間のスペースはvalを圧縮する必要あり
static t_redir	*make_new_redir(t_token *first, t_token *last)
{
	t_redir	*node;

	node = (t_redir *)ft_xmalloc(sizeof(t_redir));
	node->val = substr_from_token(first->next, last);
	node->kind = convert_redir_kind(first);
	node->next = NULL;
	return (node);
}

t_redir	*make_redir_list(t_token *tkn_ptr)
{
	t_redir	*head;
	t_redir	*new;
	t_token	*tkn_first;

	if (tkn_ptr == NULL)
		return (NULL);
	head = NULL;
	tkn_first = tkn_ptr;
	while (tkn_ptr != NULL)
	{
		if (tkn_ptr->next == NULL || is_redir_tkn(tkn_ptr->next->kind))
		{
			new = make_new_redir(tkn_first, tkn_ptr);
			add_redir_last(&head, new);
			tkn_first = tkn_ptr->next;
		}
		tkn_ptr = tkn_ptr->next;
	}
	return (head);
}
