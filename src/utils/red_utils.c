/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:41:10 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/07 15:41:11 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

void	init_pipe(t_cmd *cmd, int is_pipe)
{
	if (!is_pipe)
		cmd->output = stdo;
	else
		cmd->output = opipe;
}

/*Initializes t_redir*/
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(-print_errors(NULL));
	redir->fdr_aux = -1;
	return (redir);
}

int	check_chev_errors(t_oken *token, int *i)
{
	char	*tmp;

	if (!token[*i + 1].val)
		return (print_errors(SYNTAX"\'newline\'"), 258);
	if (*i == 0 && !ft_strncmp(token[*i].val, "|", 2))
		return (print_errors(SYNTAX"\'|\'"), 258);
	if ((ft_strncmp(token[*i].val, "|", 2) && token[*i + 1].type == red)
		|| (!ft_strncmp(token[*i].val, "|", 2)
			&& !ft_strncmp(token[*i + 1].val, "|", 2)))
	{
		tmp = ft_strjoin(SYNTAX, token[*i + 1].val);
		print_errors(tmp);
		free(tmp);
		return (258);
	}
	return (0);
}

/*initializes t_cmd (except for the char **cmd variable)*/
int	init_cmd_red(t_conxita *all, t_cmd *cmd, int *i)
{
	all->exit = check_chev_errors(all->token, i);
	if (all->exit)
		return (-1);
	if (all->token[*i].val[0] == '<' || all->token[*i].val[0] == '>')
	{
		chev_addback(&(cmd->chev),
			new_chev(all->token[*i + 1].val, all->token[*i].val));
		(*i)++;
	}
	(*i)++;
	return (0);
}
