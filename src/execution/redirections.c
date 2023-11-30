#include "../../conxita.h"

void	redirect_input(t_cmd *cmd, t_redir *redir)
{
	int	error;

	error = 0;
	if (cmd->fd_hd != -1)
		error = dup2(cmd->fd_hd, 0);
	else if (cmd->input == infile)
		error = dup2(cmd->infd, 0);
	else if (cmd->input == ipipe)
		error = dup2(redir->fdr_aux, 0);
	if (error == -1)
		print_errors(NULL);
}

void	redirect_output(t_cmd *cmd, t_redir *redir)
{
	int	error;

	error = 0;
	if (cmd->output == opipe)
		error = dup2(redir->fd_pipe[1], 1);
	else if (cmd->output == f_trunc || cmd->output == f_append)
		error = dup2(cmd->outfd, 1);
	if (error == -1)
		print_errors(NULL);
}

/*Redirects the file descriptors according with the input*/
void	redirections(t_cmd *cmd, t_redir *redir)
{
	redirect_input(cmd, redir);
	redirect_output(cmd, redir);
	close(redir->fd_pipe[0]);
	close(redir->fd_pipe[1]);
}
