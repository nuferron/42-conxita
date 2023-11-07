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

int	token_len(t_oken *token)
{
	int	i;

	i = 0;
	while (token[i].val && token[i].val[0] != '|')
		i++;
	return (i);
}

int	init_chev_input(t_oken *token, t_cmd *cmd, int i)
{
	if (token[i].val[1] == '<') // eof
	{
		if (token[i + 1].val)
		{
			cmd->heredoc = ft_strdup(token[i + 1].val);
			if (!cmd->heredoc)
				return (print_errors(NULL));
			cmd->input = heredoc;
		}
	}
	else
	{
		cmd->infile = ft_strdup(token[i].val);
		if (!cmd->infile)
			return (print_errors(NULL)); // Needs proper call to a proper error function
		cmd->input = infile;
	}
	if (!token[i + 1].val)
		exit(print_errors("\'newline\'")); // It's a little bit guarro but bueno
	return (0);
}

int	init_chev_output(t_oken *token, t_cmd *cmd, int i)
{
	int	fd;

	cmd->outfile = ft_strdup(token[i + 1].val);
	if (!cmd->outfile)
		return (print_errors(NULL));
	fd = open(cmd->outfile, O_WRONLY | O_CREAT, 0664);
	if (fd == -1)
		return (print_errors(NULL));
	if (close(fd) == -1)
		return (print_errors(NULL));
	if (token[i].val[1] == '>' && token[i + 1].val)
		cmd->output = f_append;
	else if (token[i].val[1] == '\0' && token[i + 1].val)
		cmd->output = f_trunc;
	if (!token[i + 1].val)
		exit(print_errors("\'newline\'")); // It's a little bit guarro but bueno
	return (0);
}

void	init_pipe(t_cmd *cmd, int is_pipe)
{
	if (!is_pipe)
		cmd->output = opipe;
	else
		cmd->output = opipe;
}

int	init_redir(t_oken *token, t_cmd *cmd, int i)
{
	int			ret;
	static int	is_pipe = 0;

	ret = 0;
	if (token[i].val[0] == '<')
		ret = init_chev_input(token, cmd, i);
	else if (token[i].val[0] == '>')
		ret = init_chev_output(token, cmd, i);
	else if (token[i].val[0] == '|' || is_pipe == 1)
	{
		init_pipe(cmd, is_pipe);
		is_pipe = 1;
	}
	else
		is_pipe = 0;
	return (ret);
}

int	arg_len(t_oken *token, int i)
{
	while (token[i].val && token[i].type == arg)
		i++;
	return (i);
}

void	*free_matrix(t_cmd *cmd, int i)
{
	while (i >= 0)
		free(cmd->cmd[i--]);
	free(cmd->cmd);
	return (NULL);
}

int	init_arg(t_oken *token, t_cmd *cmd, int i)
{
	int	j;

	j = 0;
	cmd->cmd = (char **)malloc(sizeof(char *) * (arg_len(token, i) + 1));
	if (!cmd->cmd)
		return (print_errors(NULL));
	while (token[i].val && token[i].type == arg)
	{
		cmd->cmd[j] = ft_strdup(token[i++].val);
		if (!cmd->cmd[j])
		{
			cmd->cmd = free_matrix(cmd, j);
			return (print_errors(NULL));
		}
		printf("init arg\tcmd->cmd[%d] = %s\n", j, cmd->cmd[j]);
		j++;
	}
	cmd->cmd[j] = NULL;
	return (i);
}

t_cmd	*token_to_cmd(t_oken *token)
{
	t_cmd	*cmd;
	int		i;
	int		j;

	i = 0;
	j = 0;
	cmd = malloc(sizeof(t_cmd) * token_len(token) + 1);
	if (!cmd)
	{
		print_errors(NULL);
		return (NULL); // Needs proper call to a proper error function
	}
	while (token[i].val)
	{
		if (token[i].type == red)
		{
			init_redir(token, &cmd[j], i++);
			if (token[i - 1].val[0] != '|')
				i++;
		}
		if (token[i].type == arg)
		{
			i = init_arg(token, &cmd[j], i);
			if (i == -1)
				return (NULL); // free stuff
		}
		if (token[i].val && token[i].val[0] == '|')
			j++;
	}
	return (cmd);
}
/*
int	main()
{
	t_oken	*token;
	t_cmd	*cmd;

	token = (t_oken *)malloc(sizeof(t_oken) * 8);
	token[0].type = arg;
	token[0].val = ft_strdup("cat");

	token[1].type = arg;
	token[1].val = ft_strdup("file1");

	token[2].type = red;
	token[2].val = ft_strdup("|");

	token[3].type = arg;
	token[3].val = ft_strdup("wc");

	token[4].type = arg;
	token[4].val = ft_strdup("-l");

	token[5].type = red;
	token[5].val = ft_strdup(">");

	token[6].type = arg;
	token[6].val = ft_strdup("file5");

	token[7].val = NULL;

	cmd = token_to_cmd(token);

	int	i = 0;
	int	j = token_len(token);
	printf("main pre while |%s|\n", cmd[i].cmd[0]);
	int	k = 0;
	while (i < j)
	{
		k = 0;
		while (cmd[i].cmd[k])
		{
			printf("main cmd[%d] = %s\n", i, cmd[i].cmd[k]);
			k++;
		}
		printf("\n");
		i++;
	}
	exit(1);
}*/