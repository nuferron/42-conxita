/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:44:20 by blvilarn          #+#    #+#             */
/*   Updated: 2023/11/06 19:38:40 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h" 

//Prompt tokenizer
t_oken	*glorified_ft_split(char *prompt, char **env)
{
	int		i;
	int		token_num;
	t_oken	*tokens;

	i = 0;
	prompt = ft_strtrim(expand_env(env, prompt), " ");
	printf("%s\n", prompt);
	token_num = get_token_num(prompt);
	tokens = ft_calloc(token_num + 1, sizeof(t_oken));
	if (!tokens)
		return (NULL);
	populate_tokens(prompt, tokens);
	free (prompt);
	while (i < token_num)
	{
		printf("%i. [%s]\n", i, tokens[i].val);
		i++;
	}
	return (tokens);
}
