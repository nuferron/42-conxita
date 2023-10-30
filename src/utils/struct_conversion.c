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
	while (token && token[i])
		i++;
	return (i);
}

/*I need to specify e_out / e_in (f*ck)
 I'm not returning anything if everything works!
 Aren't > and >> the same? The only difference is the e_out
 Should I do init_redir_input / output instead of simple / double?*/

int	init_red_input(t_oken *token, t_cmd *cmd, int i)
{
	if (token[i].val[1] == '<') // eof
	{
		if (token[i + 1])
		{
			cmd.heredoc = ft_strdup(token[i + 1]);
			if (!cmd.heredoc)
				return (print_errors(NULL));
		}
	}
	else if (token[i].val[1] == '\0')
	{
		cmd.infile = ft_strdup(token[i]);
		if (!cmd.infile)
			return (print_errors(NULL)); // Needs proper call to a proper error function
	}
	return (0);
}

int	init_redir_simple(t_oken *token, t_cmd *cmd, int i)
{
	if (token[i].val[0] == '<')
	{
		if (token[i + 1])
		{
			cmd.infile = ft_strdup(token[i]);
			if (!cmd.infile)
				return (print_errors(NULL)); // Needs proper call to a proper error function
		}
	}
	else if (token[i].val[0] == '>')
	{
		if (token[i + 1])
		{
			cmd.outfile = ft_strdup(token[i]);
			if (!cmd.outfile)
				return (print_errors(NULL));
			cmd.outfd = open(token[i + 1], O_WRONLY | O_CREAT | 0664);
			if (cmd.outfd == -1)
				return (print_errors(NULL));
			if (close(cmd.outfd) == -1)
				return (print_errors(NULL));
		}
	}
	if (!token[i + 1])
		exit(print_errors("\'newline\'")); // It's a little bit guarro but bueno
}

int	init_redir_double(t_oken *token, t_cmd *cmd, int i)
{
	if (token[i].val[0] == '<') // eof
	{
		if (token[i + 1])
		{
			cmd.heredoc = ft_strdup(token[i + 1]);
			if (!cmd.heredoc)
				return (print_errors(NULL));
		}
	}
	else if (token[i].val[0] == '>') // red out + append
	{
		
	}
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
		return (print_errors(NULL)); // Needs proper call to a proper error function
	while (token[i] && token[i].val[0] != '|')
	{
		if (token[i].type == red)
			init_redir(token, &cmd[j], i++);
		if (token[i].type == )
	}
}

int	main()
{
	t_oken	*token;
	t_cmd	*cmd;

	printf("hola\n");
	token = (t_oken *)malloc(sizeof(t_oken) * 4);
	token[0].type = bin;
	token[0].val = ft_strdup("cat");
	token[1].type = file;
	token[1].val = ft_strdup("file1");
	token[2].type = red;
	token[2].val = ft_strdup("|");
	token[3] = NULL;
	cmd = token_to_cmd(token);
	int	i = 0;
	printf("main pre while |%s|\n", cmd->cmd[i]);
	while (cmd->cmd[i])
	{
		printf("main cmd[i] = %s\n", cmd->cmd[i]);
		i++;
	}
}
