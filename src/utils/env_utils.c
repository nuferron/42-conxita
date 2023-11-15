#include "../../conxita.h"

int	path_count(const char *s, char c)
{
	int	i;
	int	counter;

	i = 0;
	counter = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			counter++;
		i++;
	}
	return (counter + 1);
}

char	*search_env(t_env *env, char *key)
{
	while (env && ft_strncmp(key, env->key, ft_strlen(key)))
		env = env->next;
	return (env->value);
}

int	len_to_char(char *str, char c)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

char	*mini_split(char *path, int	count)
{
	int		i;
	int		skip;
	char	*tmp;
	char	*result;

	i = 0;
	skip = 0;
	while (path[i] != '/')
		i++;
	while (skip < count)
	{
		if (path[i] == ':')
			skip++;
		i++;
	}
	tmp = ft_substr(path, i, len_to_char(&path[i], ':'));
	if (!tmp)
		return (NULL);
	result = ft_strjoin(tmp, "/");
	free(tmp);
	return (result);
}

int	mat_len(char **mat)
{
	int	i;

	i = 0;
	while (mat && mat[i])
		i++;
	return (i);
}

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

t_env	*env_to_lst(char **sys_env)
{
	t_env	*env;
	int		len;
	int		i;

	i = 0;
	len = mat_len(sys_env);
	env = (t_env *)malloc(sizeof(t_env) * len);
	if (!env)
		return (NULL); // future me: error management is missing!
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
/*
int	main(int argc, char **argv, char **env)
{
	t_env *tenv;

	(void)argc;
	(void)argv;
	tenv = env_to_lst(env);
	if (!tenv)
		return (-1);
	while (tenv)
	{
		printf("key: %s\tvalue: %s\n", tenv->key, tenv->value);
		tenv = tenv->next;
	}
	return (0);
}*/
