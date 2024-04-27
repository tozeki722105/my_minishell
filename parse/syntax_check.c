/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:39:52 by username          #+#    #+#             */
/*   Updated: 2024/04/12 17:34:09 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

void	print_syntax_error_free(t_token **head, t_token *error_token)
{
	t_token	*temp;

	temp = NULL;
	if (error_token->kind == TKN_PIPE)
		printf ("-bash: syntax errror near unexpected token '|'\n");
	else
		printf ("-bash: syntax error near unexpected token 'newline'\n");
	while (*head != NULL)
	{
		temp = (*head)->next;
		free (*head);
		*head = temp;
	}
}

t_token	*next_cmd(t_token *current)
{
	if (current->next == NULL)
		return (NULL);
	if (current->next->kind == TKN_SPACE)
	{
		current = current->next;
		while (current != NULL && current->kind == TKN_SPACE)
			current = current->next;
		return (current);
	}
	return (current->next);
}

bool	is_syntax_error_pipe(t_token **head, t_token *current)
{
	t_token	*next;

	if (current->kind == TKN_PIPE)
	{
		next = next_cmd (current);
		if (next == NULL)
		{
			print_syntax_error_free (head, current);
			return (TRUE);
		}
		if (next->kind == TKN_PIPE \
			|| next->kind == TKN_IN_FILE \
			|| next->kind == TKN_HEREDOC \
			|| next->kind == TKN_OUT_FILE \
			|| next->kind == TKN_APPEND_FILE)
		{
			print_syntax_error_free (head, next);
			return (TRUE);
		}
	}
	return (NULL);
}

bool	is_syntax_error_redirect(t_token **head, t_token *current)
{
	t_token	*next;

	if (current->kind == TKN_IN_FILE || current->kind == TKN_OUT_FILE \
		|| current->kind == TKN_HEREDOC || current->kind == TKN_APPEND_FILE)
	{
		next = next_cmd (current);
		if (next == NULL)
		{
			print_syntax_error_free (head, current);
			return (TRUE);
		}
		if (next->kind == TKN_PIPE \
			|| next->kind == TKN_IN_FILE \
			|| next->kind == TKN_HEREDOC \
			|| next->kind == TKN_OUT_FILE \
			|| next->kind == TKN_APPEND_FILE)
		{
			print_syntax_error_free (head, next);
			return (TRUE);
		}
	}
	return (FALSE);
}

void	syntax_check(t_token **head)
{
	t_token	*current;

	current = *head;
	if ((*head)->kind == TKN_PIPE)
		print_syntax_error_free (head, current);
	while (current != NULL)
	{
		if (is_syntax_error_pipe (head, current))
			return ;
		if (is_syntax_error_redirect (head, current))
			return ;
		current = current->next;
	}
}

//bool	is_syntax_error_outfile(t_token **head, t_token *current)
//{
//t_token *next_cmd;

//if (current->kind == TKN_OUT_FILE || current->kind == TKN_IN_FILE 
//		|| current->kind == TKN_)
//	{
//		next_cmd = next_cmd (current);
//		if (next_cmd == NULL)
//		{
//			print_syntax_error_free (head, current);
//			return (TRUE);
//		}
//		if (next_cmd->kind == TKN_OUT_FILE
//			|| next_cmd->kind == TKN_IN_FILE
//			|| next_cmd->kind == TKN_HEREDOC
//			|| next_cmd->kind == TKN_OUT_FILE
//			|| next_cmd->kind == TKN_APPEND_FILE)
//		{
//			print_syntax_error_free (head, next_cmd);
//			return (TRUE);
//		}
//	}
//	return (FALSE);
//}
