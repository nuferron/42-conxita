#include "../../conxita.h"

// > file cmd
// cmd
// < file cmd
// cmd << eof
// << eof cat
// cmd arg
// cmd arg > file arg
// cmd >> file
// >> file cmd

/*Sets all t_cmd variables to either NULL or -1*/
t_cmd	*set_cmd_to_null(int len)
{
	int		i;
	t_cmd	*cmd;

	i = 0;
	cmd = malloc(sizeof(t_cmd) * len);
	if (!cmd)
	{
		print_errors(NULL);
		return (NULL);
	}
	while (i < len)
	{
		cmd[i].cmd = NULL;
		cmd[i].heredoc = NULL;
		cmd[i].infile = NULL;
		cmd[i].outfile = NULL;
		cmd[i].infd = -1;
		cmd[i].outfd = -1;
		cmd[i].input = stdi;
		cmd[i].output = stdo;
		i++;
	}
	return (cmd);
}

t_cmd	*token_to_cmd(t_oken *token, t_env *env)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		len;

	i = 0;
	j = 0;
	len = cmd_count(token, 0) + 1;
	cmd = set_cmd_to_null(len);
	if (!cmd)
		return (NULL);
	while (j < len)
	{
		if (token[i].type == red)
			init_cmd_red(token, &cmd[j], &i);
		else if (i > 0 && !cmd[j].input && token[i - 1].val[0] == '|')
		{
			if (cmd[j].input == stdi)
				cmd[j].input = ipipe;
			if (j > 0 && cmd[j - 1].output == stdo)
				cmd[j - 1].output = opipe;
		}
		else if (token[i].type == arg)
		{
			i = init_cmd_cmd(token, &cmd[j], i, env);
			if (i == -1)
				return (NULL); // free stuff
		}
		if (!token[i].val || (token[i].val && token[i].val[0] == '|'))
			j++;
	}
	dprintf(2, "\033[1;31mttc: cmd %s\tinfile %s\tinput %d\033[0m\n", cmd->cmd[0], cmd->infile, cmd->input);
	return (cmd);
}
