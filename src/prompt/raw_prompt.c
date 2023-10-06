/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:44:20 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/05 20:37:04 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h" 

void	write_single(t_comp *comps, int *i, char c, enum e_arg_type type)
{
	comps[*i].val = (char *)ft_calloc(2, sizeof(char));
	comps[*i].val[0] = c;
	comps[*i].type = type;
	(*i)++;
}

int	get_word_len(char *prompt, int i, char *delimiters)
{
	int	len;

	len = 0;
	while (!ft_strchr(delimiters, prompt[i + len]))
		len++;
	return (len);
}

void	write_word(char *prompt, t_comp *comps, int	*i, int *comp_i)
{
	int	j;
	int	len;
	int	zero;

	j = 0;
	len = get_word_len(prompt, *i, "'\" ");
	zero = 0;
	if (!i)
		i = &zero;
	comps[*comp_i].val = (char *)ft_calloc(len + 1, sizeof(char));
	if (!comps[*comp_i].val)
		return ;
	while (!ft_strchr("'\" ", prompt[*i]))
	{
		comps[*comp_i].val[j] = prompt[*i];
		(*i)++;
		j++;
	}
}

void	populate_comps(char *prompt, t_comp *comps)
{
	int		i;
	int		comp_i;

	i = 0;
	comp_i = 0;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			write_single(comps, &comp_i, ' ', spc);
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'' || prompt[i] == '"')
			handle_single(prompt, comps, &i, &comp_i);
		if (!ft_strchr("'\" ", prompt[i]))
		{
			comp_i++;
			write_word(prompt, comps, &i, &comp_i);
		}
	}
}

//ft_split_plus
t_comp	*glorified_ft_split(char *prompt)
{
	int		i;
	int		comp_num;
	t_comp	*comps;

	i = 0;
	comp_num = get_comp_num(prompt);
	comps = ft_calloc(comp_num + 1, sizeof(t_comp));
	if (!comps)
		return (NULL);
	populate_comps(prompt, comps);
	while (i < comp_num)
	{
		printf("%i. [%s]\n", i, comps[i].val);
		i++;
	}
	return (comps);
}
