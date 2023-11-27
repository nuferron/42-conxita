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
		env[i].show = 1;
		env[i].next = NULL;
		i++;
	}
	return (env);
}

/*if print = 0 it copies the behaviour of env
  if print = 1 it copies the behaviour of export*/
char	*get_env_var(t_env *env, int print)
{
	int		len;
	int		i;
	char	*var;

	len = ft_strlen(env->key);
	i = -1;
	if (env->show)
		len += ft_strlen(env->value) + 3;
	var = (char *)ft_calloc(len + 1, sizeof (char));
	if (!var)
		return (NULL);
	while (env->key[++i])
		var[i] = env->key[i];
	if (!env->show)
		return (var);
	var[i++] = '=';
	if (print)
		var[i++] = '\"';
	len = 0;
	while (env->value[len])
		var[i++] = env->value[len++];
	if (print)
		var[i] = '\"';
	return (var);
}

/*Converts t_env to char **
  print = 0 -> empty variables SHOULD NOT be printed
  print = 1 -> empty variables SHOULD be printed*/
char	**env_to_mat(t_env *env, int print)
{
	char	**sys_env;
	int		len;
	int		i;
	int		j;

	i = -1;
	j = 0;
	len = env_len(env);
	sys_env = (char **)ft_calloc(len + 1, sizeof (char *));
	if (!sys_env)
		exit((unsigned char)print_errors(NULL));
	while (++i < len)
	{
		if (!env[i].show && !print)
			continue ;
		sys_env[j] = get_env_var(&env[i], print);
		if (!sys_env[j++])
			exit((unsigned char)print_errors(NULL));
	}
	return (sys_env);
}
