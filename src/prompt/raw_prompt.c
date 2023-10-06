/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raw_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:44:20 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/06 20:30:40 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h" 

// 
t_comp	*glorified_ft_split(char *prompt)
{
	int		i;
	int		comp_num;
	t_comp	*comps;

	i = 0;
	(void)prompt;
	//comp_num = get_comp_num(prompt);
	comp_num = 0;
	comps = ft_calloc(comp_num + 1, sizeof(t_comp));
	if (!comps)
		return (NULL);
	//populate_comps(prompt, comps);
	while (i < comp_num)
	{
		printf("%i. [%s]\n", i, comps[i].val);
		i++;
	}
	return (comps);
}
