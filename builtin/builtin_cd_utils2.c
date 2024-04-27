/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:39:44 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 17:57:01 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

void	print_path_list(t_path *ptr)
{
	while (ptr != NULL)
	{
		printf("val=%s;\n", ptr->val);
		ptr = ptr->next;
	}
}

static t_path	*make_new_path(char *first, char *last, t_bool no_slash_flag)
{
	char	*tmp_val;
	t_path	*new;

	new = (t_path *)ft_xmalloc(sizeof(t_path));
	tmp_val = ft_xsubstr(first, 0, (size_t)(last - first + 1));
	if (no_slash_flag)
	{
		new->val = ft_xstrjoin(tmp_val, "/");
		free(tmp_val);
	}
	else
		new->val = tmp_val;
	new->next = NULL;
	return (new);
}

static t_path	*find_last_path(t_path *ptr)
{
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

static void	add_path_last(t_path **head, t_path *new)
{
	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	find_last_path(*head)->next = new;
}

t_path	*make_path_list(char *path_ptr)
{
	t_path	*new;
	t_path	*head;
	t_bool	no_slash_flag;
	char	*last;

	head = NULL;
	no_slash_flag = FALSE;
	while (*path_ptr != '\0')
	{
		last = ft_strchr(path_ptr, '/');
		if (last == NULL)
		{
			last = ft_strchr(path_ptr, '\0') - sizeof(char);
			no_slash_flag = TRUE;
		}
		new = make_new_path(path_ptr, last, no_slash_flag);
		add_path_last(&head, new);
		path_ptr = last + sizeof(char);
	}
	return (head);
}
