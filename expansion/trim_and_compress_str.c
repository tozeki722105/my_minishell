/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_and_compress_str.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toshi <toshi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 19:47:31 by toshi             #+#    #+#             */
/*   Updated: 2024/04/27 20:48:08 by toshi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansion.h"
#include "../utils/utils.h"
#include "../libft/libft.h"

static size_t count_compress_len(char *str, char *set)
{
	size_t len;
	size_t i;

	len = 0;
	i = 0;
	while (str[i])
	{
		if (ft_strchr(set, str[i]))
		{
			while(str[i] && ft_strchr(set, str[i]))
				i++;
		}
		else
			i++;
		len++;
	}
	return (len);
}

static void strlcpy_compressed(char *dest, char *src, size_t len, char *set)
{
	size_t	dest_i;
	size_t	i;

	dest_i = 0;
	i = 0;
	while (src[i] && dest_i + 1 < len)
	{
		if (ft_strchr(set, src[i]))
		{
			while(src[i] && ft_strchr(set, src[i]))
				i++;
			dest[dest_i++] = ' ';
		}
		else
			dest[dest_i++] = src[i++];
	}
	dest[dest_i] = '\0';
}

char *trim_and_compress_str(char *str, char *set)
{
	char *trimed_str;
	char *compressed_str;
	size_t len;

	trimed_str = ft_xstrtrim(str, " \t\n");
	len = count_compress_len(trimed_str, set);
	compressed_str = (char *)ft_xmalloc(sizeof(char) * (len + 1));
	strlcpy_compressed(compressed_str, trimed_str, len + 1, set);
	free(trimed_str);
	return (compressed_str);
}
