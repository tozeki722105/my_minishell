/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/05/03 17:54:42 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include "../minishell.h"

# define CHILD			0
# define EXIST			0
# define NOT_EXIST		-1
# define DEFAULT		0
# define ERROR_STATUS	1

enum	e_pipefd_direct
{
	R	= 0,
	W	= 1
};

typedef struct s_exec_date
{
	int		prevfd_in;
	size_t	fork_count;
	pid_t	last_pid;
	t_bool	last_cmd_flag;
}t_exec_data;

//~~~~execute start~~~~
//execute.c
void	execute(t_tree_node *root, t_manager *manager);
//execute_utils.c
t_bool	is_single_builtin(t_tree_node *root);
//exec_cmds.c
void	exec_cmds(t_tree_node *ptr, t_manager *manager);
//exec_cmds_utils.c
pid_t	fork_and_exec_cmd(t_adv_data adv, t_manager *manager, \
		t_exec_data *exec);
void	wait_child(t_manager *manager, t_exec_data exec);
//exec_external_cmd.c
void	exec_external_cmd(char **cmd_args, t_manager *manager);
//do_sigle_builtin.c
void	do_single_builtin(t_tree_node *root, t_manager *manager);
int		do_builtin(char **cmd_args, t_manager *manager, t_bool parent_flag);
//try_change_stream_redirect.c
t_bool	try_change_stream_redirect(t_redir *redir_list, int dest_fd);
//~~~~~~~~

//~~~~heredoc start~~~~
//try_heredoc.c
void	try_heredoc(t_tree_node *ptr, t_manager *manager);
//try_heredoc_utils.c
char	*create_tmpfile_path(void);
void	perror_eof_in_heredoc(t_manager *manager, char *delim);
void	remove_heredoc_tmpfile(t_tree_node *ptr);

#endif