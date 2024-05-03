/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/31 13:24:13 by toshi             #+#    #+#             */
/*   Updated: 2024/05/03 18:05:27 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include "../libft/libft.h"
#include "../utils/utils.h"

static char	*find_start_and_set_sign(char *ptr, int *sign)
{
	while (*ptr && (*ptr == ' ' || *ptr == '\t' || *ptr == '\n' \
			|| *ptr == '\v' || *ptr == '\f' || *ptr == '\r'))
		ptr++;
	if (*ptr == '+' || *ptr == '-')
	{
		if (*ptr == '-')
			*sign = -1;
		ptr++;
	}
	return (ptr);
}

//startからend内に数値が入っているか、またend移行スペース以外の文字が入っていないか確認
static t_bool	validate_and_set_end(char *ptr, char **end)
{
	t_bool	flag;

	flag = FALSE;
	while (*ptr && ft_isdigit(*ptr))
	{
		flag = TRUE;
		ptr++;
	}
	*end = ptr;
	while (*ptr && *ptr == ' ')
		ptr++;
	if (*ptr || flag == FALSE)
		return (FALSE);
	return (TRUE);
}

static t_bool	is_long_over(const long num, const char c, int sign)
{
	if (sign > 0)
	{
		if (num > (LONG_MAX / 10))
			return (TRUE);
		else if (num == (LONG_MAX / 10) && (c - '0') > (LONG_MAX % 10))
			return (TRUE);
	}
	else if (sign < 0)
	{
		if (num < (LONG_MIN / 10))
			return (TRUE);
		else if (num == (LONG_MIN / 10) && (c - '0') > -(LONG_MIN % 10))
			return (TRUE);
	}
	return (FALSE);
}

static t_bool	validate_and_set_num(const char *str, int *ans_num)
{
	int		sign;
	char	*start;
	char	*end;
	long	num;

	sign = 1;
	start = find_start_and_set_sign((char *)str, &sign);
	if (!validate_and_set_end(start, &end))
		return (FALSE);
	num = 0;
	while (start != end)
	{	
		if (is_long_over(num, *start, sign))
			return (FALSE);
		num = (num * 10) + (sign * (*start - '0'));
		start++;
	}
	*ans_num = (int)num;
	return (TRUE);
}

int	do_exit(char **cmd_args, t_manager *manager, t_bool parent_flag)
{
	size_t	argc;
	int		num;

	argc = count_strs(cmd_args);
	if (argc == 1)
	{
		try_print_exit(parent_flag);
		exit (ft_atoi(manager->exit_status));
	}
	if (!validate_and_set_num(cmd_args[1], &num))
	{
		try_print_exit(parent_flag);
		perror_arg3("exit", cmd_args[1], "numeric argument required");
		exit (2);
	}
	else if (argc > 2)
	{
		perror_arg2("exit", "too many arguments");
		return (1);
	}
	try_print_exit(parent_flag);
	exit ((unsigned char)num);
}
