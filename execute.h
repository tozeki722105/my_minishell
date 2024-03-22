/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:29:28 by tofujiwa          #+#    #+#             */
/*   Updated: 2024/03/20 19:22:49 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include "libft/libft.h"
#include "stdbool.h"

#define	SYS_FAILURE	-1
#define	CHILD		0
#define EXIST		0
#define NOT_EXIST	-1
#define DEFAULT		0
#define AMBIGUOUS	NULL

enum	e_pipefd_direct
{
	R	= 0,
	W	= 1
};

typedef enum e_bool
{
	FALSE	= 0,
	TRUE	= 1
}	t_bool;

enum e_token_kind
{
	TKN_SPACE,
	TKN_TEXT,
	TKN_S_QUOTE,
	TKN_D_QUOTE,
	TKN_ENV,
	TKN_PIPE,
	TKN_IN_FILE,
	TKN_HEREDOC,
	TKN_OUT_FILE,
	TKN_APPEND_FILE,
};

enum e_redir_kind
{
	AMBIGUOUS_REDIR,
	REDIR_IN_FILE,
	REDIR_HEREDOC,
	REDIR_HEREDOC_NO_EXPAND,
	REDIR_OUT_FILE,
	REDIR_APPEND_FILE
};

typedef struct s_token
{
	enum e_token_kind	kind;
	char				*val;
	struct s_token		*next;
}	t_token;

typedef struct s_redir
{
	enum e_redir_kind	kind;
	char				*val;
	struct s_redir		*next;
}	t_redir;

typedef struct s_env
{
	char				*original;
	char				*key;
	char				*val;
	t_bool				printed_flag;
	struct s_env		*next;
}	t_env;

typedef struct s_base_data
{
	t_token				*cmd_tokens;
	t_token				*infile_tokens;
	t_token				*outfile_tokens;
}	t_base_data;

typedef struct s_refine_data
{
	char				**cmd_args;
	t_redir				*infile_paths;
	t_redir				*outfile_paths;
}	t_refine_data;

typedef struct s_tree_node
{
	t_base_data			base_data;
	t_refine_data		refine_data;
	struct s_tree_node	*prev;
	struct s_tree_node	*left;
	struct s_tree_node	*right;
}	t_tree_node;

typedef struct s_manager
{
	t_env	*env_list;
	int		exit_status;
	int		prev_outfd;
	size_t	fork_count;
	pid_t	last_pid;
	bool	last_cmd_flag;
}	t_manager;

//~~~~utils start~~~~
//bool_utils.c
t_bool		is_ifs(char c);
t_bool		is_quote(char c);
t_bool		is_delim(char c);
t_bool		is_valuable_tkn(enum e_token_kind kind);
t_bool		is_in_redir_tkn(enum e_token_kind kind);
t_bool		is_out_redir_tkn(enum e_token_kind kind);
t_bool		is_redir_tkn(enum e_token_kind kind);
t_bool		is_last_cmd(t_tree_node *ptr);
t_bool		is_first_cmd(t_tree_node *ptr);
t_bool		is_cmd_node(t_tree_node *ptr);
t_bool		is_cmd_path(char *first_cmd_arg);
t_bool		is_equal_str(const char *s1, char *s2);
t_bool		is_builtin(char *cmd);
//env_utils.c
size_t		count_envname(char *dollar_ptr);
char		*ft_getenv(const char *env_name, t_env *head);
char		*getenv_in_str(char *dollar_ptr, size_t env_name_len, t_manager manager);
//free_utils.c
void		free_multi_strs(char **strs);
void		free_tkn(t_token *tkn);
void		free_tkn_list(t_token *head);
void		free_env_list(t_env *env_list);
void		free_base_data(t_base_data base_data);
void		free_tnode_list(t_tree_node *head);
//libftwrap_utils.c
void		perror_arg2(char *errtarget, char *errstr);
void		perror_arg2_and_exit(char *errtarget, char *errstr, int exit_status);
void		perror_and_exit(char *err_title, int exit_status);
char		*ft_xstrdup(const char *s1);
char		*ft_xstrtrim(const char *s1, const char *set);
char		*ft_xsubstr(const char *s, unsigned int start, size_t len);
char		*ft_xstrjoin(const char *s1, const char *s2);
char		**ft_xsplit(const char *s, char c);
//print_utils.c
void		wc(char *str);
void		print_to_last(char *begining, char *last);
void		print_tkn_list(t_token *head);
void		print_env_list(t_env *head);
void		print_cmd_args(char **strs);
void		print_redir_list(t_redir *head);
void		print_init_of_tnode_list(t_tree_node *tnode_ptr);
void		print_exec_of_tnode_list(t_tree_node *tnode_ptr);
//syswrap_utils.c
void		ft_free(void **ptr);
void		*ft_xmalloc(size_t size);
void		*ft_xrealloc(void *ptr, size_t size);
void		*ft_xcalloc(size_t count, size_t size);
int			ft_xdup2(int copied_fd, int dest_fd);
void		ft_xclose(int fd);
void		ft_xpipe(int *pipefd);
pid_t		ft_xfork(void);
int			ft_xunlink(char *pathname);
void		ft_xexecve(char *cmd_path, char **cmd_args, t_env *env_list);
//tkn_utils.c
t_token		*find_last_tkn(t_token *head);
t_token		*find_last_valuable_tkn(t_token *head);
t_token		*search_prev_tkn(t_token *head, t_token *target);
void		add_tkn_last(t_token **head, t_token *new);
void		remove_tkn(t_token **head, t_token *ptr, t_token *prev);
char		*substr_from_tkn(t_token *begining, t_token *last);
//utils.c
char		*ulltonbase(unsigned long long num, unsigned int base);
size_t		strlcat_ret_catlen(char *dest, const char *src, size_t size);
char		*join_and_free_str2(char *str1, char *str2);
//~~~~utils end~~~~

//~~~~ initi start~~~~
t_manager	init(void);
//~~~~~~~~

//~~~~ tokenize start~~~~
t_token		*tokenize(char *line_ptr);

t_token		*make_new_tkn(char *begining, ssize_t count, enum e_token_kind kind);
ssize_t		count_untill_ifs_last(char *begining);
//~~~~~~~~

//~~~~ parse start~~~~
t_tree_node *parse(t_token *tkn_ptr);
//~~~~~~~~

//~~~~expansion start~~~~
void	expansion(t_tree_node *ptr, t_manager manager);
char	*expand_env_in_dquote(char *str, t_manager manager);
//~~~~~~~~

//~~~~execute start~~~~
void	_exec(t_tree_node *ptr, t_manager *manager);
//~~~~~~~~

//~~~~heredoc start~~~~
void	remove_tmpfile(t_tree_node *tnode_head);
void	try_heredoc(t_tree_node *tnode_head, t_manager manager);
//~~~~~~~~

#endif 