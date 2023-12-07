/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:44:24 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/07 15:44:25 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

static void	free_matrix(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->cmd)
		return ;
	while (cmd->cmd[i])
		free(cmd->cmd[i++]);
	free(cmd->cmd);
}

static void	free_chev(t_chev *chev)
{
	t_chev	*tmp;

	tmp = chev;
	while (tmp)
	{
		free(chev->file);
		tmp = tmp->next;
		free(chev);
		chev = tmp;
	}
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	if (!cmd)
		return ;
	len = cmd[0].len;
	while (i < len)
	{
		free_matrix(&cmd[i]);
		free_chev(cmd[i].chev);
		i++;
	}
	free(cmd);
}

void	*free_the_tokens(t_oken *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i].val)
	{
		free(tokens[i].val);
		i++;
	}
	free(tokens);
	return (NULL);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(env->key);
		free(env->value);
		tmp = tmp->next;
		free(env);
		env = tmp;
	}
}
