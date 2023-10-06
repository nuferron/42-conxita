#include "../../conxita.h"

void	handle_quotes_len(char *prompt, int *i, int *len)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	(*len)++;
	if (prompt[*i] && prompt[*i] != quote)
		(*len)++;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	if (prompt[*i] == quote)
	{
		(*i)++;
		(*len)++;
	}
}

//Get number of components for a raw prompt
int	get_comp_num(char *prompt)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			len++;
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'' || prompt[i] == '"')
			handle_quotes_len(prompt, &i, &len);
		if (prompt[i] && ft_strchr("'\" ", prompt[i]) == NULL)
			len++;
		while (prompt[i] && ft_strchr("'\" ", prompt[i]) == NULL)
			i++;
	}
	return (len);
}
