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

void	d_quote_len(char *prompt, int *i, int *len)
{
	(*i)++;
	while (prompt[*i] && prompt[*i] != '"')
	{
		(*len)++;
		(*i)++;
	}
	(*i)++;
}
