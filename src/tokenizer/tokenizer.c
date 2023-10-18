/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:44:20 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/11 13:39:53 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h" 

//Prompt tokenizer
t_oken	*glorified_ft_split(char *prompt)
{
	//int		i;
	int		token_num;
	t_oken	*tokens;

	//i = 0;
	token_num = get_token_num(prompt);
	printf("%i\n", token_num);
	tokens = ft_calloc(token_num + 1, sizeof(t_oken));
	if (!tokens)
		return (NULL);
	populate_tokens(prompt, tokens);
	// while (i < token_num)
	// {
	// 	printf("%i. [%s]\n", i, tokens[i].val);
	// 	i++;
	// }
	return (tokens);
}
