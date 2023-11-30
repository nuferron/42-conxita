#include "../../conxita.h"

void	free_matrix(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
		free(cmd->cmd[i++]);
	free(cmd->cmd);
}

void	*free_the_tokens(t_oken *tokens)
{
	int	i;

	i = 0;
	while (tokens && tokens[i].val)
	{
		free(tokens[i].val);
		i++;
	}
	if (tokens)
		free(tokens);
	return (NULL);
}

void	free_cmd(t_cmd *cmd)
{
	int	i;
	int	len;

	i = 0;
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
	int	i;

	i = 0;
	while (env[i].next)
	{
		free(env[i].key);
		free(env[i].value);
		i++;
	}
	free(env[i].key);
	free(env[i].value);
	free(env);
}
