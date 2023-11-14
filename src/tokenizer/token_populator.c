#include "../../conxita.h"

static int	get_word_len(char *prompt, int i)
{
	int	len;

	len = 0;
	while (!ft_strchr(" <>|", prompt[i]))
	{
		if (prompt[i] == '\'' || prompt[i] == '"')
			quote_len(prompt, &i, &len);
		if (!ft_strchr("'\" <>|", prompt[i]))
		{
			len++;
			i++;
		}
	}
	return (len);
}

static void	handle_word(char *prompt, t_oken *tokens, int *i, int *pos)
{
	int	word_len;
	int	j;

	word_len = get_word_len(prompt, *i);
	j = 0;
	tokens[*pos].val = ft_calloc(word_len + 1, sizeof(char *));
	if (!tokens[*pos].val)
		return ;//!FREE ALL - MEMORY LEAKS
	while (!ft_strchr("<>| ", prompt[*i]))
	{
		if (prompt[*i] == '\'' || prompt[*i] == '"')
			fill_quotes(prompt, &tokens[*pos], i, &j);
		if (!ft_strchr("<>|'\" ", prompt[*i]))
		{
			tokens[*pos].val[j] = prompt[*i];
			(*i)++;
			j++;
		}
	}
	tokens[*pos].type = arg;
	(*pos)++;
}

static void	handle_delimiter(char *prompt, t_oken *tokens, int *i, int *pos)
{
	char	c;

	c = 0;
	while (prompt[*i] == ' ')
		(*i)++;
	if (ft_strchr("<>|", prompt[*i]))
	{
		c = prompt[*i];
		if (c && prompt[*i + 1] == c)
		{
			(*i)++;
			tokens[*pos].val = ft_calloc(3, sizeof(char));
			tokens[*pos].val[1] = c;
		}
		else
			tokens[*pos].val = ft_calloc(2, sizeof(char));
		tokens[*pos].val[0] = c;
		if (c)
			(*i)++;
		tokens[*pos].type = red;
		(*pos)++;
	}
	while (prompt[*i] == ' ')
		(*i)++;
}

void	populate_tokens(char *prompt, t_oken *tokens)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	while (prompt[i])
	{
		if (ft_strchr("<>| ", prompt[i]))
			handle_delimiter(prompt, tokens, &i, &pos);
		if (!ft_strchr(" <>|", prompt[i]))
			handle_word(prompt, tokens, &i, &pos);
	}
}
