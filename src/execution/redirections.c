#include "../../conxita.h"

/*Redirects the file descriptors according with the input*/
/*int	redirections(t_cmd *cmd, t_redir *redir)
{
	if (!cmd->chev)
		return (0);
	if (init_chev(cmd->chev, cmd->last) == -1)
		return (-1);
	if (cmd->chev->type == here || cmd->chev->type == in)
	{
		if (dup2(cmd->last[0], 0) == -1)
			exit(-print_errors(NULL));
	}
	else if (cmd->chev->type == outt || cmd->chev->type == outa)
	{
		if (dup2(cmd->last[1], 1) == -1)
			exit(-print_errors(NULL));
	}
	else if (cmd->input == ipipe)
	{
		if (dup2(redir->fd_pipe[0], 0) == -1)
			exit(-print_errors(NULL));
	}
	else if (cmd->output == opipe)
	{
		if (dup2(redir->fd_pipe[1], 1) == -1)
			exit(-print_errors(NULL));
	}
	return (0);
}
*/
int	redirections(t_cmd *cmd, t_redir *redir)
{
	if (cmd->input == ipipe)
		cmd->last[0] = redir->fdr_aux;
	if (cmd->output == opipe)
		cmd->last[1] = redir->fd_pipe[1];
	if (init_chev(cmd->chev, cmd->last) == -1)
		return (-1);
	if (cmd->last[0] > 0 && dup2(cmd->last[0], 0) == -1)
		exit(-print_errors(NULL));
	if (cmd->last[1] > 0  && dup2(cmd->last[1], 1) == -1)
		exit(-print_errors(NULL));
	return (0);
}

int init_chev(t_chev *chev, int *last)
{
	while (chev)
	{
		if (last[0] != -1 && (chev->type == in || chev->type == here))
			close(last[0]);
		if (last[1] != -1 && (chev->type == outt || chev->type == outa))
			close(last[1]);
		if (chev->type == outt)
			last[1] = open(chev->file, O_WRONLY | O_CREAT | O_TRUNC, 0664);
		else if (chev->type == outa)
			last[1] = open(chev->file, O_WRONLY | O_CREAT | O_APPEND, 0664);
		if ((chev->type == outt || chev->type == outa) && last[1] < 0)
			return (print_errors(chev->file));
		if (chev->type == here)
			last[0] = chev->fd;
		else if (chev->type == in)
			last[0] = open(chev->file, O_RDONLY);
		if (chev->type == in && chev->fd < 0)
			return (print_errors(chev->file));
		chev = chev->next;
	}
	return (0);
}
