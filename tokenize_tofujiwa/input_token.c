/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/25 19:50:11 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/04/12 17:34:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

ssize_t	input_token(t_token **head, char *line)
{
	char	*start;
	int		kind;

	start = line;
	while (*line != '\0' && *line == '<' && line - start <= 1)
		line++;
	if (*start == '<' && *(start + 1) == '<')
		kind = TKN_HEREDOC;
	else
		kind = TKN_IN_FILE;
	token_list (head, start, line - start, kind);
	return (line - start);
}
