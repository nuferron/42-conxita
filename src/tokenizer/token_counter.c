#include "../../conxita.h"

static void	handle_quotes_len(char *prompt, int *i)
{
	char	quote;

	quote = prompt[*i];
	(*i)++;
	while (prompt[*i] && prompt[*i] != quote)
		(*i)++;
	(*i)++;
}

static void	handle_delimiter(char *prompt, int *i, int *len)
{
	char	c;

	c = 0;
	while (prompt[*i] == ' ')
		(*i)++;
	if (ft_strchr("<>|", prompt[*i]))
	{
		c = prompt[*i];
		(*i)++;
		if (prompt[*i] == c)
			(*i)++;
		(*len)++;
	}
	while (prompt[*i] == ' ')
		(*i)++;
	(*len)++;
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
		if (ft_strchr("<>| ", prompt[i]))
			handle_delimiter(prompt, &i, &len);
		if (prompt[i] == '\'' || prompt[i] == '"')
			handle_quotes_len(prompt, &i);
		if (!ft_strchr("'\" <>|", prompt[i]))
			i++;
	}
	return (len);
}
