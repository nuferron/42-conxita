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
	char	last_char;

	equal = 0;
	while (env[equal] != '=' && env[equal] != '\0')
		equal++;
	if (flag == 0)
	{
		last_char = env[equal];
		env[equal] = '\0';
		str = env;
	}
	else
	{
		if (env[equal] == '\0')
			return (NULL);
		str = &env[equal + 1];
	}
	return (str);
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
	int		j;

	j = 0;
	len = env_len(env);
	sys_env = (char **)ft_calloc(len + 1, sizeof (char *));
	if (!sys_env)
		exit(print_errors(NULL) * (-1));
	while (env)
	{
		if (!env->show && !print)
			continue ;
		sys_env[j] = get_env_var(env, print);
		if (!sys_env[j++])
			exit(print_errors(NULL) * (-1));
		env = env->next;
	}
	return (sys_env);
}
