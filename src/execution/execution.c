/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:37:00 by nuferron          #+#    #+#             */
/*   Updated: 2023/12/13 17:26:31 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../conxita.h"

void	exec_no_builtins(t_cmd *cmd, t_env *env)
{
	char	*tmp;

	tmp = cmd->cmd[0];
	cmd->cmd[0] = get_path(env, tmp);
	free(tmp);
	if (execve(cmd->cmd[0], cmd->cmd, env_to_mat(env, 0)) == -1)
	{
		if (access(cmd->cmd[0], X_OK) == -1)
			ft_dprintf(2, "conxita: %s: command not found\n", cmd->cmd[0]);
		else
			print_errors(NULL);
	}
	exit(127);
}

// replace return (1) by a call to the function. It will return the exit code
int	exec_cmd(t_cmd *cmd, t_conxita *all)
{
	if (!cmd->cmd)
		return (0);
	if (!ft_strncmp(cmd->cmd[0], "echo", 5))
		return (builtin_echo(&(cmd->cmd[1])));
	else if (!ft_strncmp(cmd->cmd[0], "cd", 3))
		return (builtin_cd(&(cmd->cmd[1]), all->env));
	else if (!ft_strncmp(cmd->cmd[0], "pwd", 4))
		return (builtin_pwd());
	else if (!ft_strncmp(cmd->cmd[0], "export", 7))
		return (builtin_export(&(cmd->cmd[1]), &(all->env)));
	else if (!ft_strncmp(cmd->cmd[0], "unset", 6))
		return (builtin_unset(&(cmd->cmd[1]), all));
	else if (!ft_strncmp(cmd->cmd[0], "env", 4))
		return (builtin_env(all->env));
	else if (!ft_strncmp(cmd->cmd[0], "exit", 5))
		return (builtin_exit(&(cmd->cmd[1]), all));
	else
		exec_no_builtins(cmd, all->env);
	return (0);
}

int	exec_multiple_cmd(t_conxita *all, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	pid = 0;
	while (++i < len)
	{
		if (pipe(all->redir->fd_pipe) == -1)
			exit(-print_errors(NULL));
		pid = fork();
		if (pid == 0)
		{
			if (redirections(&(all->cmd[i]), all->redir) == -1)
				exit(1);
			exit(exec_cmd(&(all->cmd[i]), all));
		}
		close(all->redir->fd_pipe[1]);
		close(all->redir->fdr_aux);
		all->redir->fdr_aux = all->redir->fd_pipe[0];
	}
	return (pid);
}

int	exec_one_builtin(t_conxita *all)
{
	int	fd[2];
	int	ret;

	fd[0] = dup(0);
	fd[1] = dup(1);
	if (redirections(all->cmd, all->redir) == -1)
	{
		close(fd[0]);
		close(fd[1]);
		return (1);
	}
	ret = exec_cmd(all->cmd, all);
	if (dup2(fd[0], 0) == -1)
		exit(-print_errors(NULL));
	if (dup2(fd[1], 1) == -1)
		exit(-print_errors(NULL));
	return (ret);
}

int	lets_execute(t_conxita *all, int len)
{
	pid_t	pid;
	int		i;

	i = -1;
	if (len == 1 && all->cmd->cmd && is_builtin(all->cmd->cmd[0]))
		return (exec_one_builtin(all));
	pid = exec_multiple_cmd(all, len);
	close(all->redir->fdr_aux);
	return (ft_waitpid(pid, len));
}
