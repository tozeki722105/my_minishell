/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_new_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:01:37 by toshi             #+#    #+#             */
/*   Updated: 2024/04/27 20:40:20 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../utils/utils.h"

//lenはクォーテーション内の文字数+1文字分
static char	*_substr_into_quote(char *first, size_t count)
{
	if (*first == '$')
	{
		first++;
		count--;
	}
	return (ft_xsubstr(first, 1, count - 2));
}

// is_quote(*last)で判断したいのは、クォートトークンか{$""/$''}の形かどうか
t_token	*make_new_token(char *first, ssize_t count, enum e_token_kind kind)
{
	t_token	*node;

	node = (t_token *)ft_xmalloc(sizeof(t_token));
	if (is_quote(first[count - 1]))
		node->val = _substr_into_quote(first, (size_t)count);
	else
		node->val = ft_xsubstr(first, 0, (size_t)count);
	node->kind = kind;
	node->next = NULL;
	return (node);
}
