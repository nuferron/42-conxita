#include "../../conxita.h"


int	get_path()
{
	char	*user;
	char	*pwd;
	char	*path;
	char	*tmp;
	char	*all_paths;

	user = getenv("USER");
	if (user)
	{
		all_paths = ft_strjoin(user, ":");
		free(user);
		if (!all_paths)
			return (-1);
	}
	pwd = getenv("PWD");
	if (pwd)
	{
		user = ft_strjoin(pwd, ":");
		free(pwd);
		if (!user)
			return (-1);

	}
	path = getenv("PATH");
	if (!user && !pwd && !path)
	{
		return (-1);
	}
	all_paths = ft_strjoin(user, );
	printf("path %s\n", path);
	return (0);
}

int	main()
{
	get_path();
}



/*
void	redirecting_fd(int cmd_id, int argc, t_data *data)
{
	if (cmd_id == 2 && data->fd1 != -1)
	{
		dup2(data->fd1, 0);
		dup2(data->fd_pipe[1], 1);
	}
	else if (cmd_id == 2)
	{
		dup2(data->fd_pipe[1], 1);
	}
	else if (cmd_id == argc - 2)
	{
		dup2(data->pipe_tmp, 0);
		dup2(data->fd2, 1);
	}
	else
	{
		dup2(data->pipe_tmp, 0);
		dup2(data->fd_pipe[1], 1);
		close(data->fd1);
	}
}

int	pipex(int argc, char **argv, char **env, t_data *data)
{
	int		i;
	char	**tmp;

	i = 2;
	data->pipe_tmp = -1;
	while (i < argc - 1)
	{
		pipe(data->fd_pipe);
		data->path = getting_full_path(argv[i++], get_path(env));
		if (fork() == 0)
		{
			tmp = ft_split(argv[i], ' ');
			redirecting_fd(i, argc, data);
			if (execve(data->path, tmp, env) == -1)
			{
				ft_printf(2, "Error: %s: command not found\n", tmp[0]);
				exit(1);
			}
		}
		close(data->fd_pipe[1]);
		close(data->pipe_tmp);
		data->pipe_tmp = data->fd_pipe[0];
		free(data->path);
	}
	close(data->pipe_tmp);
	return (1);
}*/
/*
int	main(int argc, char **argv, char **env)
{
	t_data	data;

	if (argc < 5)
		return (ft_errors("arg"));
	data.fd1 = open(argv[1], O_RDONLY);
	data.fd2 = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (data.fd1 == -1)
		ft_errors(argv[1]);
	if (data.fd2 == -1)
		ft_errors(argv[argc - 1]);
	pipex(argc, argv, env, &data);
	close(data.fd2);
	waitpid(0, &data.status, 0);
	return (WEXITSTATUS(data.status));
}*/
