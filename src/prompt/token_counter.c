#include "../../conxita.h"

static void	handle_quotes(char *prompt, int *i)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	(*i)++;
}

//Get number of tokens for a raw prompt
int	get_token_num(char *prompt)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (prompt[0])
		len++;
	while (prompt[i])
	{
		if (prompt[i] == ' ')
			len++;
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == '\'' || prompt[i] == '"')
			handle_quotes(prompt, &i);
		while (!ft_strchr("'\" ", prompt[i]))
			i++;
	}
	return (len);
}
