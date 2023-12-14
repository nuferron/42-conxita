/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_variable.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:30:17 by blvilarn          #+#    #+#             */
/*   Updated: 2023/12/13 19:30:18 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

void	skip_unexpandable(char *str, int *i)
{
	if (str[*i] == '\'')
	{
		(*i)++;
		while (str[*i] && str[*i] != '\'')
			(*i)++;
		if (str[*i])
			(*i)++;
	}
	else if (ft_strnstr(&str[*i], "<<", 2))
	{
		(*i) += 2;
		while (str[*i] == ' ')
			(*i)++;
		while (!ft_strchr("<>| '\"", str[*i]))
			(*i)++;
	}
}

int	is_quoted(char *full, char *str, int i)
{
	int		j;
	int		len;
	bool	quotes;
	bool	simple;

	j = 0;
	len = ft_strlen(full) - ft_strlen(str) + i;
	quotes = false;
	simple = false;
	while (full[j] && j < i)
	{
		if (full[j] == '\'' && !quotes)
			simple = !simple;
		if (full[j++] == '\"' && !simple)
			quotes = !quotes;
	}
	return (quotes);
}

char	*get_pos(char *str, char *old, char *full_str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && !is_quoted(full_str, str, i))
			|| ft_strnstr(&str[i], "<<", 2))
		{
			skip_unexpandable(str, &i);
			i--;
		}
		while (str[i] == old[j])
		{
			i++;
			if (old[++j] == '\0')
				return (&str[i - j]);
		}
		j = 0;
		if (str[i])
			i++;
	}
	return (NULL);
}

static void	replace(char *str, char *new_str, char *old, char *new)
{
	int		i;
	char	*pos;
	char	*first_position;

	i = 0;
	first_position = &str[0];
	pos = get_pos(str, old, first_position);
	while (pos)
	{
		while (str != pos)
			*new_str++ = *str++;
		while (new[i])
		{
			*new_str = new[i];
			i++;
			new_str++;
		}
		i = 0;
		str += ft_strlen(old);
		pos = get_pos(str, old, first_position);
	}
	while (*str)
		*new_str++ = *str++;
}

char	*replace_variable(char *str, char *old, char *new)
{
	char	*new_str;

	if (!str || !old || !new)
		return (NULL);
	if (!get_pos(str, old, str))
		return (ft_strdup(str));
	new_str = ft_calloc(get_len(str, old, new) + 1, sizeof(char));
	if (!new_str)
		return (NULL);
	replace(str, new_str, old, new);
	return (new_str);
}
