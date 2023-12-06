#include "../../conxita.h"

char	*check_input(char *str)
{
	if (ft_strchr(str, '/') && access(str, X_OK) == 0)
		return (ft_strdup(str));
	else if (ft_strchr(str, '/') && access(str, X_OK) == -1)
	{
		print_errors(str);
		exit(127);
	}
	return (NULL);
}

/*Returns an isolated path from the environment variable*/
char	*get_path(t_env *env, char *str)
{
	char	*path;
	int		i;
	int		total;

	i = 0;
	path = check_input(str);
	if (path)
		return (path);
	while (env && ft_strncmp(env->key, "PATH", 4))
		env = env->next;
	if (!env && access(str, X_OK) == 0)
		return (ft_strdup(str));
	else if (!env)
		return (ft_strdup(str));
	total = path_count(env->value, ':');
	while (i < total)
	{
		path = ft_strjoin_free(minisplit(env->value, i++), str);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
	}
	return (ft_strdup(str));
}

/*Initializes char **cmd (NULL-terminated) from struct t_cmd.
 It tries to add a path to the first element. If no valid path is found,
 it will put the received value (token[i].val)*/
int	init_cmd_cmd(t_oken *token, t_cmd *cmd, int i, t_env *env)
{
	int	j;
	int	len;

	(void)env;
	j = get_arg_number(cmd->cmd);
	if (!token)
		return (-1);
	len = arg_count(token, i);
	if (!cmd->cmd)
		cmd->cmd = (char **)malloc(sizeof(char *) * (len + 1));
	if (!cmd->cmd)
		exit(-print_errors(NULL));
	while (token[i].val && token[i].type == arg)
	{
			cmd->cmd[j] = ft_strdup(token[i].val);
		if (!cmd->cmd[j])
			exit(-print_errors(NULL));
		i++;
		j++;
	}
	cmd->cmd[j] = NULL;
	return (i);
}
