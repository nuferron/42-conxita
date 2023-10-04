/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:44:20 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/04 20:07:36 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

void	handle_quotes_len(char *prompt, int *i, int *len)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	(*len)++;
	if (prompt[*i] && prompt[*i] != quote)
		(*len)++;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	if (prompt[*i] == quote)
	{
		i++;
		(*len)++;
		printf("AMAQUOTE\n");
	}
}

//Get number of components for a raw prompt
static int	get_comp_num(char *prompt)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'' || prompt[i] == '"')
			handle_quotes_len(prompt, &i, &len);
		//printf("MIDDLE: %")
		if (prompt[i] && ft_strchr("'\" ", prompt[i]) == NULL)
			len++;
		while (prompt[i] && ft_strchr("'\" ", prompt[i]) == NULL)
			i++;
	}
	return (len);
}

//ft_split_plus
int	glorified_ft_split(char *prompt)
{
	int		i;

	i = 0;
	printf("%i\n", get_comp_num(prompt));
	return (i);
}
