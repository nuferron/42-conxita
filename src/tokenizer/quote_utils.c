#include "../../conxita.h"

//Adds len everything but the quotes and leaves i to point 
//at the last quote position + 1
void	quote_len(char *prompt, int *i, int *len)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
	{
		(*len)++;
		(*i)++;
	}
	if (prompt[*i] != '\0')
		(*i)++;
}

void	fill_quotes(t_data *d, int *j)
{
	char	quote;

	quote = d->prompt[d->i];
	d->i++;
	while (d->prompt[d->i] && d->prompt[d->i] != quote)
	{
		d->tokens[d->pos].val[*j] = d->prompt[d->i];
		d->i++;
		(*j)++;
	}
	d->i++;
}

