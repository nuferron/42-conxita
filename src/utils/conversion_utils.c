/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:43:39 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/07 15:43:46 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

/*Sets all t_cmd variables to either NULL or -1*/
t_cmd	*cmd_to_null(int len)
{
	int		i;
	t_cmd	*cmd;

	i = -1;
	cmd = malloc(sizeof(t_cmd) * len);
	if (!cmd)
		exit((unsigned char)print_errors(NULL));
	while (++i < len)
	{
		cmd[i].cmd = NULL;
		cmd[i].input = stdi;
		cmd[i].output = stdo;
		cmd[i].chev = NULL;
		cmd[i].len = len;
		cmd[i].last[0] = -1;
		cmd[i].last[1] = -1;
	}
	return (cmd);
}

/*Converts t_oken to a t_cmd*/
t_cmd	*token_to_cmd(t_conxita *all, int len)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	all->cmd = cmd_to_null(len);
	while (j < len)
	{
		if (i && j && !ft_strncmp(all->token[i - 1].val, "|", 2))
			all->cmd[j].input = ipipe;
		if (i && j && !all->token[i - 1].type && all->token[i - 1].val[0] == '|'
			&& all->cmd[j - 1].output == stdo)
			all->cmd[j - 1].output = opipe;
		if (all->token[i].val && all->token[i].type == red)
		{
			if (init_cmd_red(all, &all->cmd[j], &i))
				return (NULL);
		}
		else if (all->token[i].type == arg)
			i = init_cmd_cmd(all->token, &all->cmd[j], i, all->env);
		if (!all->token[i].val || !ft_strncmp(all->token[i].val, "|", 2))
			j++;
	}
	return (all->cmd);
}
