#include "../../conxita.h"

void	exec_no_builtins(t_cmd *cmd, t_env *env)
{
	if (execve(cmd->cmd[0], cmd->cmd, env_to_mat(env, 0)) == -1)
	{
		if (access(cmd->cmd[0], X_OK) == -1)
		{
			ft_putstr_fd("conxita: ", 2);
			ft_putstr_fd(cmd->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
		}
		else
			print_errors(NULL);
	}
	exit(127);
}

// replace return (1) by a call to the function. It will return the exit code
int	exec_cmd(t_cmd *cmd, t_env *env)
{
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (builtin_echo(cmd->cmd));
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (0);
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (0);
	else
		exec_no_builtins(cmd, env);
	return (0);
}

int	exec_multiple_cmd(t_cmd *cmd, t_env *env, t_redir *redir, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	while (++i < len)
	{
		if (pipe(redir->fd_pipe) == -1)
			return (print_errors(NULL));
		pid = fork();
		if (pid == 0)
		{
			redirections(&cmd[i], redir);
			exit(exec_cmd(&cmd[i], env));
		}
		close(cmd[i].outfd);
		close(redir->fd_pipe[1]);
		close(redir->fdr_aux);
		close(cmd->fd_hd);
		close(cmd->infd);
		redir->fdr_aux = redir->fd_pipe[0];
	}
	return (pid);
}

int	exec_one_cmd(t_cmd *cmd, t_env *env, t_redir *redir)
{
	int	fd[2];
	int	ret;

	fd[0] = dup(0);
	fd[1] = dup(1);
	redirections(cmd, redir);
	ret = exec_cmd(cmd, env);
	close(cmd->infd);
	close(cmd->outfd);
	return (ret);
}

int	lets_execute(t_cmd *cmd, t_redir *redir, t_env *env, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (!cmd || !redir)
		return (print_errors(NULL));
	if (len == 1 && is_builtin(cmd->cmd[0]))
		return (exec_one_cmd(cmd, env, redir));
	pid = exec_multiple_cmd(cmd, env, redir, len);
	close(redir->fdr_aux);
	return (pid);
}
