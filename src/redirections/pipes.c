#include "../../conxita.h"

int	test_paths(char *path, t_cmd *cmd)
{
	int		total;
	int		count;
	char	*test;
	char	*split;

	count = -1;
	total = path_count(path, ':');
	while (++count < total)
	{
		split = mini_split(path, count);
		if (!split)
			return (-2);
		test = ft_strjoin(split, cmd->cmd[0]);
		free(split);
		if (access(test, X_OK) == 0)
			break ;
		free(test);
	}
	if (count == total)
		return (-1);
	cmd->cmd[0] = ft_strdup(test);
	free(test);
	return (0);
}

int	get_path(char **env, t_cmd *cmd)
{
	char	*path;
	int		error;

	if (ft_strchr(cmd->cmd[0], '/') && access(cmd->cmd[0], X_OK) == 0)
		return (0);
	else if (ft_strchr(cmd->cmd[0], '/') && access(cmd->cmd[0], X_OK) != 0)
		return (-1);
	path = search_env(env, "PATH=");
	if (!path)
		return (-2);
	error = test_paths(path, cmd);
	return (error);
}
/*
int	main(int argc, char **argv, char **env)
{
	t_cmd	*cmd;
	int		res;

	(void)argc;
	(void)argv;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	cmd->cmd = (char **)malloc(sizeof(char *) * 3);
	cmd->cmd[0] = ft_strdup("asdf");
	cmd->cmd[1] = ft_strdup("-e");
	cmd->cmd[2] = NULL;
	
	res = get_path(env, cmd);
	printf("is exec? %d\ncmd changed? cmd %s\tflags %s\n", res, cmd->cmd[0], cmd->cmd[1]);
	free(cmd->cmd[0]);
	free(cmd->cmd[1]);
	free(cmd->cmd);
	free(cmd);
}*/
