/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_wrap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:11:11 by toshi             #+#    #+#             */
/*   Updated: 2024/04/12 18:43:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenize.h"

t_token  *tokenize_wrap(char *line)
{
	t_token *head;
	
	head = NULL;
	if (split_to_token(&head, line) == -1)
		return (NULL);
	return (head);
}