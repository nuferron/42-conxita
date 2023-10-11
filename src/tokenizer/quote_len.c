#include "../../conxita.h"

//Add len everything but the quotes and leave i to point 
//at the last quote position + 1
void	s_quote_len(char *prompt, int *i, int *len)
{
	(*i)++;
	while (prompt[*i] != '\'')
	{
		(*len)++;
		(*i)++;
	}
	(*i)++;
}

void	d_quote_len(char *prompt, int *i, int *len)
{
	(*i)++;
	while (prompt[*i] != '"')
	{
		(*len)++;
		(*i)++;
	}
	(*i)++;
}
hola que 
