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

	//dprintf(2, "init chev out: outfile %s\n", token[*i + 1].val);
	if (!token[*i + 1].val)
		return (print_errors("\'newline\'"));
	cmd->outfile = ft_strdup(token[*i + 1].val);
	if (!cmd->outfile)
		exit((unsigned char)print_errors(NULL));
	fd = open(cmd->outfile, O_WRONLY | O_CREAT, 0664);
	if (fd == -1)
		return (print_errors(NULL));
	if (close(fd) == -1)
		return (print_errors(NULL));
	if (token[*i].val[1] == '>' && token[*i + 1].val)
		cmd->output = f_append;
	else if (token[*i].val[1] == '\0' && token[*i + 1].val)
		cmd->output = f_trunc;
	cmd->outfd = get_out_fd(cmd);
	(*i)++;
	return (0);
}

/*Initializes t_cmd when there's either "<" or "<<"*/
int	init_chev_input(t_oken *token, t_cmd *cmd, int *i)
{
	if (token[*i].val[1] == '<')
	{
		if (!token[*i + 1].val)
			return (0);
		close(cmd->fd_hd);
		exec_heredoc(cmd, token[++(*i)].val);
	}
	else
	{
		if (*i > 0 && !token[*i + 1].val)
			return(print_errors("\'newline\'"));
		cmd->infile = ft_strdup(token[++(*i)].val);
		if (!cmd->infile)
			exit((unsigned char)print_errors(NULL));
		cmd->input = infile;
		close(cmd->infd);
		cmd->infd = open(cmd->infile, O_RDONLY);
		if (cmd->infd == -1)
			return (print_errors(cmd->infile));
	}
	return (0);
}

/*Initializes t_redir*/
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit((unsigned char)print_errors(NULL));
	redir->saved_std[0] = dup(0);
	redir->saved_std[1] = dup(1);
	if (redir->saved_std[0] == -1 || redir->saved_std[1] == -1)
		exit(print_errors("stdin/stdout"));
	redir->fdr_aux = -1;
	return (redir);
}

/*Opens and returns the output's fd. It can be truncated (>) or appended (>>)*/
int	get_out_fd(t_cmd *cmd)
{
	int	fd;

	fd = 0;
	close(cmd->outfd);
	if (cmd->output == f_trunc)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	else if (cmd->output == f_append)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (fd == -1)
		return (print_errors(NULL));
	return (fd);
}

