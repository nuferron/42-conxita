#include "../../conxita.h"

/*Searches key as an env variable and returns its value as a string*/
char	*search_env(t_env *env, char *key)
{
	while (env && ft_strncmp(key, env->key, ft_strlen(key)))
		env = env->next;
	if (!env)
		return (NULL);
	return (env->value);
}

/*Separates the variable name (flag == 0) from its value (flag == 1)*/
char	*splitting_env(char *env, int flag)
{
	char	*str;
	int		equal;

	equal = 0;
	while (env[equal] != '=' && env[equal] != '\0')
		equal++;
	if (flag == 0)
	{
		env[equal] = '\0';
		str = env;
	}
	else
		str = &env[equal + 1];
	return (str);
}

/*Converts the system environment to a t_env variable*/
t_env	*env_to_lst(char **sys_env)
{
	t_env	*env;
	int		len;
	int		i;

	i = 0;
	len = mat_len(sys_env);
	env = (t_env *)malloc(sizeof(t_env) * len);
	if (!env)
	{
		print_errors(NULL);
		return (NULL);
	}
	while (i < len)
	{
		env[i].key = ft_strdup(splitting_env(sys_env[i], 0));
		env[i].value = ft_strdup(splitting_env(sys_env[i], 1));
		if (i > 0)
			env[i - 1].next = &env[i];
		env[i].next = NULL;
		i++;
	}
	return (env);
}
