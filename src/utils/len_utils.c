/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:44:10 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/07 21:18:17 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

int	arg_count(t_oken *token, int start)
{
	int	count;

	count = 0;
	while (token[start].val && ft_strncmp(token[start].val, "|", 2))
	{
		if (ft_strncmp(token[start].val, "<", 2)
			|| ft_strncmp(token[start].val, ">", 2)
			|| (start && ft_strncmp(token[start - 1].val, "<", 2))
			|| (start && ft_strncmp(token[start - 1].val, ">", 2)))
			count++;
		start++;
	}
	return (count);
}

int	cmd_count(t_oken *token, int i)
{
	int	j;

	j = 0;
	while (token[j].val)
	{
		if (token[j].val[0] == '|')
			i++;
		j++;
	}
	return (i);
}

int	env_len(t_env *env)
{
	int	i;

	i = 0;
	if (!env)
		return (0);
	while (env)
	{
		env = env->next;
		i++;
	}
	return (i);
}

int	get_arg_number(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

int	get_len(char *str, char *old, char *new)
{
	int		len;
	char	*pos;

	len = ft_strlen(str);
	pos = get_pos(str, old, str);
	while (pos)
	{
		len -= ft_strlen(old);
		len += ft_strlen(new);
		pos = get_pos(pos + 1, old, str);
	}
	return (len);
}
