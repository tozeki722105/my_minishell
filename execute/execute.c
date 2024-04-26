/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tozeki <tozeki@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 00:12:17 by toshi             #+#    #+#             */
/*   Updated: 2024/04/26 19:09:13 by tozeki           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static void	handle_sigint_in_exec(int num)
{
	g_signal_flag = 128 + num;
	ft_putchar_fd('\n', STDERR_FILENO);
}

//cat | cat と cat | ls で出力が違う 
static void	handle_sigquit_in_exec(int num)
{
	g_signal_flag = 128 + num;
	ft_putendl_fd("Quit: 3", STDERR_FILENO);
}

void	execute(t_tree_node *root, t_manager *manager)
{
	int	tmpfd_in;

	tmpfd_in = ft_xdup(STDIN_FILENO);
	try_heredoc(root, manager);
	if (g_signal_flag == 0)
	{
		signal(SIGINT, handle_sigint_in_exec);
		signal(SIGQUIT, handle_sigquit_in_exec);
		if (is_single_builtin(root))
			do_single_builtin(root, manager);
		else
			exec_cmds(root, manager);
	}
	else
		update_exit_status(manager, g_signal_flag);
	ft_xdup2(tmpfd_in, STDIN_FILENO);
	ft_xclose(tmpfd_in);
	remove_heredoc_tmpfile(root);
}
