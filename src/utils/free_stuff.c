#include "../../conxita.h"

void	free_matrix(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->cmd)
		return ;
	while (cmd->cmd[i])
		free(cmd->cmd[i++]);
	free(cmd->cmd);
}

void	*free_the_tokens(t_oken *tokens)
{
	int	i;

	i = 0;
	if (!tokens)
		return (NULL);
	while (tokens[i].val)
	{
		free(tokens[i].val);
		i++;
	}
	free(tokens);
	return (NULL);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
	if (!cmd)
		return ;
	len = cmd[0].len;
	while (i < len)
	{
		free_matrix(&cmd[i]);
		free(cmd[i].heredoc);
		free(cmd[i].infile);
		free(cmd[i].outfile);
		i++;
	}
	free(cmd);
}

void	free_env(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		free(env->key);
		free(env->value);
		tmp = tmp->next;
		free(env);
		env = tmp;
	}
}

void	free_all(t_conxita *all)
{
	free_the_tokens(all->token);
	free_cmd(all->cmd);
	free(all->redir);
	all->cmd = NULL;
	all->token = NULL;
	all->redir = NULL;
}
