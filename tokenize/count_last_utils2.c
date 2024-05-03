/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_last_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 01:03:24 by toshi             #+#    #+#             */
/*   Updated: 2024/05/01 01:11:51 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"
#include "../utils/utils.h"
#include "../libft/libft.h"

//最初の文字がalphaか_以外ならそこで区切り、1を返す
// ex) $$ $? $6 $@
//文字中の数字、_、文字が対象->alnum+_か
static ssize_t	count_env_last(char *ptr)
{
	ssize_t	count;
	
	if (!(ft_isalpha(*ptr) || *ptr == '_'))
		return (1);
	count = 0;
	while (*ptr && (ft_isalnum(*ptr) || *ptr == '_'))
	{
		count++;
		ptr++;
	}
	return (count);
}

//nextがクォートなら、1($)+クォートのカウント
//nextが$以外のdelimなら、1($)のみ
//nextがalphaか_以外なら2($+next)
ssize_t	count_dollar_last(char *first)
{
	char	*next;
	ssize_t	count;

	next = first + sizeof(char);
	if (is_quote(*next))
	{
		count = count_quote_last(next);
		if (count == -1)
			return (-1);
		return (1 + count);
	}
	if (is_delim(*next) && *next != '$')
		return (1);
	return (1 + count_env_last(next));
}
// if (*next != '_' && !ft_isalpha(*next)) // !(next=='_' || ft_isalpha(*next))
	// 	return (2);
// char	*next;
// ssize_t	count;

// next = first + sizeof(char);
// if (*next == '?' || *next == '$')
// 	return (2);
// if (is_quote(*next))
// {
// 	count = count_quote_last(next);
// 	if (count == -1)
// 		return (-1);
// 	return (1 + count);
// }
// if (*next == '\0' || is_delim(*next))
// 	return (1);
// return (1 + count_text_last(next));