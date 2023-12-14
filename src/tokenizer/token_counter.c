/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_counter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 19:30:20 by blvilarn          #+#    #+#             */
/*   Updated: 2023/12/13 19:30:21 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

static void	handle_quotes_len(char *prompt, int *i)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	if (prompt[*i] != '\0')
		(*i)++;
}

static void	handle_delimiter(char *prompt, int *i, int *len)
{
	char	c;

	while (prompt[*i] == ' ')
		(*i)++;
	if (ft_strchr("<>|", prompt[*i]))
	{
		c = prompt[*i];
		if (c != '\0' && prompt[*i] == c)
			(*i)++;
		(*len)++;
	}
	while (prompt[*i] == ' ')
		(*i)++;
	(*len)++;
}

//Get number of tokens for a raw prompt
int	get_token_num(char *prompt)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (prompt[0])
		len++;
	while (prompt[i])
	{
		if (ft_strchr("<>| ", prompt[i]))
			handle_delimiter(prompt, &i, &len);
		if (prompt[i] == '\'' || prompt[i] == '"')
			handle_quotes_len(prompt, &i);
		if (!ft_strchr("'\" <>|", prompt[i]))
			i++;
	}
	return (len);
}
