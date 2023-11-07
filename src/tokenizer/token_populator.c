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

static void	handle_word(t_data *d)
{
	int	word_len;
	int	j;

	word_len = get_word_len(d->prompt, d->i);
	j = 0;
	d->tokens[d->pos].val = ft_calloc(word_len + 1, sizeof(char *));
	if (!d->tokens[d->pos].val)
		return ;//!FREE ALL - MEMORY LEAKS
	while (!ft_strchr("<>| ", d->prompt[d->i]))
	{
		if (d->prompt[d->i] == '\'' || d->prompt[d->i] == '"')
			fill_quotes(d, &j);
		if (!ft_strchr("<>|'\" ", d->prompt[d->i]))
		{
			d->tokens[d->pos].val[j] = d->prompt[d->i];
			d->i++;
			j++;
		}
	}
	d->pos++;
}

static void	handle_delimiter(t_data *d)
{
	char	c;

	c = 0;
	while (d->prompt[d->i] == ' ')
		d->i++;
	if (ft_strchr("<>|", d->prompt[d->i]))
	{
		c = d->prompt[d->i];
		if (c && d->prompt[d->i + 1] == c)
		{
			d->i++;
			d->tokens[d->pos].val = ft_calloc(3, sizeof(char));
			d->tokens[d->pos].val[1] = c;
		}
		else
			d->tokens[d->pos].val = ft_calloc(2, sizeof(char));
		d->tokens[d->pos].val[0] = c;
		if (c)
			d->i++;
		d->tokens[d->pos].type = red;
		d->pos++;
	}
	while (d->prompt[d->i] == ' ')
		d->i++;
}

void	populate_tokens(char *prompt, t_oken *tokens)
{
	t_data	data;

	data.prompt = prompt;
	data.tokens = tokens;
	data.i = 0;
	data.pos = 0;
	while (prompt[data.i])
	{
		if (ft_strchr("<>| ", prompt[data.i]))
			handle_delimiter(&data);
		if (!ft_strchr(" <>|", prompt[data.i]))
			handle_word(&data);
	}
}
