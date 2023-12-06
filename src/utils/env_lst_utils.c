#include "../../conxita.h"

t_env	*new_env(char *env_var)
{
	t_env	*node;

	node = malloc(sizeof (t_env));
	if (!node)
		exit(print_errors(NULL) * (-1));
	node->value = NULL;
	node->key = ft_strdup(splitting_env(env_var, 0));
	if (splitting_env(env_var, 1))
		node->value = ft_strdup(splitting_env(env_var, 1));
	if (!node->key)
		exit(-print_errors(NULL));
	if (node->value)
		node->show = 1;
	else
		node->show = 0;
	node->next = NULL;
	return (node);
}

t_env	*env_last(t_env *env)
{
	t_env	*current;

	if (!env)
		return (NULL);
	current = env;
	while (current->next)
		current = current->next;
	return (current);
}

void	env_addback(t_env **env, t_env *new)
{
	t_env	*last;

	if (env && new)
	{
		if (!*env)
		{
			*env = new;
			return ;
		}
		last = env_last(*env);
		last->next = new;
	}
}

/*Converts the system environment to a t_env variable*/
t_env	*env_to_lst(char **sys_env)
{
	t_env	*env;
	int		len;
	int		i;

	i = 0;
	env = NULL;
	len = get_arg_number(sys_env);
	while (i < len)
	{
		env_addback(&env, new_env(sys_env[i]));
		i++;
	}
	return (env);
}
