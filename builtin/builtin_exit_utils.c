/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 03:48:08 by toshi             #+#    #+#             */
/*   Updated: 2024/05/03 18:04:48 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"

void	try_print_exit(t_bool parent_flag)
{
	if (parent_flag)
		ft_putendl_fd("exit", STDERR_FILENO);
}
