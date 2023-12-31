/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nuferron <nuferron@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:48:37 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/14 12:22:04 by nuferron         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

static int	is_valid_export(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (i == 0 && ft_isdigit(arg[i]))
			return (0);
		if (!is_env(arg[i]) && arg[i] != '=')
			return (0);
		if (arg[i] == '=')
			return (1);
		i++;
	}
	return (1);
}

void	update_env(t_env **env, char *arg)
{
	char	*str;
	t_env	*tmp;

	str = splitting_env(arg, 0);
	tmp = search_env(*env, str);
	if (!tmp)
		env_addback(env, new_env(arg));
	else
	{
		free(tmp->key);
		tmp->key = splitting_env(arg, 0);
		if (ft_strchr(arg, '='))
		{
			free(tmp->value);
			tmp->value = splitting_env(arg, 1);
			tmp->show = 1;
			if (!tmp->key)
				exit(-print_errors(NULL));
		}
	}
	free(str);
}

static int	set_env(char **arg, t_env **env)
{
	int		i;
	int		exit_code;

	i = 0;
	exit_code = 0;
	while (arg[i])
	{
		if (!is_valid_export(arg[i]))
		{
			exit_code = 1;
			ft_dprintf(2, "conxita: export: `%s': not a valid identifier\n",
				arg[i]);
			i++;
			continue ;
		}
		update_env(env, arg[i]);
		i++;
	}
	return (exit_code);
}

int	builtin_export(char **args, t_env **env_lst)
{
	int		argn;
	t_env	*tmp;

	argn = get_arg_number(args);
	tmp = *env_lst;
	if (argn == 0)
	{
		while (tmp)
		{
			printf("declare -x %s", tmp->key);
			if (tmp->value)
				printf("=\"%s\"", tmp->value);
			printf("\n");
			tmp = tmp->next;
		}
		return (0);
	}
	return (set_env(args, env_lst));
}
