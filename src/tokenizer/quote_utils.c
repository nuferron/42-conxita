#include "../../conxita.h"

//Adds len everything but the quotes and leaves i to point 
//at the last quote position + 1
void	s_quote_len(char *prompt, int *i, int *len)
{
	(*i)++;
	while (prompt[*i] && prompt[*i] != '\'')
	{
		(*len)++;
		(*i)++;
	}
	(*i)++;
}

//TODO: Handle env variables
void	d_quote_len(char *prompt, int *i, int *len, char **env)
{
	(void)env;
	(*i)++;
	while (prompt[*i] && prompt[*i] != '"')
	{
		(*len)++;
		(*i)++;
	}
	(*i)++;
}

void	fill_s_quotes(t_data *d, int *j)
{
	d->i++;
	while (d->prompt[d->i] && d->prompt[d->i] != '\'')
	{
		d->tokens[d->pos].val[*j] = d->prompt[d->i];
		d->i++;
		(*j)++;
	}
	d->i++;
}

void	fill_d_quotes(t_data *d, int *j, char **env)
{
	(void) env;
	d->i++;
	while (d->prompt[d->i] && d->prompt[d->i] != '"')
	{
		d->tokens[d->pos].val[*j] = d->prompt[d->i];
		d->i++;
		(*j)++;
	}
	d->i++;
}
