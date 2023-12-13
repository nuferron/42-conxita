/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chev_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:43:28 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/13 19:02:53 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

t_chev	*new_chev(char *file, char *type)
{
	t_chev	*node;

	node = malloc(sizeof (t_chev));
	if (!node)
		exit(-print_errors(NULL));
	node->file = ft_strdup(file);
	if (!node->file)
		exit(-print_errors(NULL));
	node->fd = -1;
	if (!ft_strncmp(type, "<", 2))
		node->type = in;
	else if (!ft_strncmp(type, "<<", 3))
	{
		node->type = here;
		node->fd = here_doc_wrapper(file);
	}
	else if (!ft_strncmp(type, ">", 2))
		node->type = outt;
	else if (!ft_strncmp(type, ">>", 2))
		node->type = outa;
	else
		node->type = std;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

t_chev	*chev_last(t_chev *chev)
{
	t_chev	*current;

	if (!chev)
		return (NULL);
	current = chev;
	while (current->next)
		current = current->next;
	return (current);
}

void	chev_addback(t_chev **chev, t_chev *new)
{
	t_chev	*last;

	if (chev && new)
	{
		if (!*chev)
		{
			*chev = new;
			return ;
		}
		last = chev_last(*chev);
		last->next = new;
		new->prev = &last;
	}
}
