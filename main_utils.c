/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 10:37:45 by tozeki            #+#    #+#             */
/*   Updated: 2024/04/26 18:55:57 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"
#include "utils/utils.h"

static t_env	*make_env_list(void)
{
	extern char	**environ;
	size_t		i;
	t_env		*head;
	t_env		*new;

	head = NULL;
	i = 0;
	while (environ[i] != NULL)
	{
		new = make_new_env(environ[i]);
		add_env_last(&head, new);
		i++;
	}
	return (head);
}

static char	*get_current_dir(void)
{
	char	*buf;

	buf = (char *)ft_xcalloc(PATH_MAX + 1, sizeof(char));
	getcwd(buf, PATH_MAX + 1);
	return (buf);
}

t_manager	initialize(void)
{
	t_manager	manager;

	manager.env_list = make_env_list();
	manager.current_dir = get_current_dir();
	manager.exit_status = ft_xitoa(0);
	manager.heredoc_line = 0;
	return (manager);
}

void	finalize(t_manager *manager)
{
	free_env_list(manager->env_list);
	free(manager->current_dir);
	free(manager->exit_status);
}
