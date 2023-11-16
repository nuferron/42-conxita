#include "../../conxita.h"

void	init_pipe(t_cmd *cmd, int is_pipe)
{
	if (!is_pipe)
		cmd->output = stdo;
	else
		cmd->output = opipe;
}

/*Initializes t_cmd when there's either ">" or ">>"*/
int	init_chev_output(t_oken *token, t_cmd *cmd, int *i)
{
	int	fd;

	cmd->outfile = ft_strdup(token[*i + 1].val);
	if (!cmd->outfile)
		return (print_errors(NULL));
	fd = open(cmd->outfile, O_WRONLY | O_CREAT, 0664);
	if (fd == -1)
		return (print_errors("chev out"));
	if (close(fd) == -1)
		return (print_errors(NULL));
	if (token[*i].val[1] == '>' && token[*i + 1].val)
		cmd->output = f_append;
	else if (token[*i].val[1] == '\0' && token[*i + 1].val)
		cmd->output = f_trunc;
	if (!token[*i + 1].val)
		exit(print_errors("\'newline\'"));
	(*i)++;
	return (0);
}

/*Initializes t_cmd when there's either "<" or "<<"*/
int	init_chev_input(t_oken *token, t_cmd *cmd, int *i)
{
	if (token[*i].val[1] == '<')
	{
		if (token[*i + 1].val)
		{
			cmd->heredoc = ft_strdup(token[*i + 1].val);
			if (!cmd->heredoc)
				return (print_errors(NULL));
			cmd->input = heredoc;
		}
	}
	else
	{
		cmd->infile = ft_strdup(token[*i].val);
		if (!cmd->infile)
			return (print_errors(NULL));
		cmd->input = infile;
	}
	if (!token[*i + 1].val)
		exit(print_errors("\'newline\'"));
	(*i)++;
	return (0);
}

/*Initializes t_redir*/
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->saved_std[0] = dup(0);
	redir->saved_std[1] = dup(1);
	if (redir->saved_std[0] == -1 || redir->saved_std[1] == -1)
		return (NULL);
	redir->fdr_aux = -1;
	return (redir);
}