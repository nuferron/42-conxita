#include "../../conxita.h"

void	init_pipe(t_cmd *cmd, int is_pipe)
{
	if (!is_pipe)
		cmd->output = stdo;
	else
		cmd->output = opipe;
}

int	init_chev_output(t_oken *token, t_cmd *cmd, int *i)
{
	if (!token[*i + 1].val)
		return (print_errors("\'newline\'"), 258);
	chev_addback(&(cmd->chev), new_chev(token[*i + 1].val, token[*i].val));
	(*i)++;
	return (0);
}

int	init_chev_input(t_oken *token, t_cmd *cmd, int *i)
{
	if (*i > 0 && !token[*i + 1].val)
		return (print_errors("\'newline\'"), 258);
	chev_addback(&(cmd->chev), new_chev(token[*i + 1].val, token[*i].val));
	(*i)++;
	return (0);
}

/*Initializes t_redir*/
t_redir	*init_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		exit(-print_errors(NULL));
	redir->fdr_aux = -1;
	return (redir);
}
