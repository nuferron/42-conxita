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

void	fill_quotes(char *prompt, t_oken *token, int *i, int *j)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
	{
		(*token).val[*j] = prompt[*i];
		(*i)++;
		(*j)++;
	}
	(*i)++;
}

