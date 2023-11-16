#include "../../conxita.h"

static int	get_arg_len(char *prompt, int i)
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

static int	handle_arg(char *prompt, t_oken *tokens, int *i, int *pos)
{
	int	arg_len;
	int	j;

	arg_len = get_arg_len(prompt, *i);
	j = 0;
	tokens[*pos].val = ft_calloc(arg_len + 1, sizeof(char *));
	if (!tokens[*pos].val)
		return (0);
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
	return (1);
}

static int	fill_delimiter(char *prompt, t_oken *tokens, int *i, int pos)
{
	char	c;

	c = prompt[*i];
	if (c && prompt[*i + 1] == c)
	{
		(*i)++;
		tokens[pos].val = ft_calloc(3, sizeof(char));
		if (!tokens[pos].val)
			return (0);
		tokens[pos].val[1] = c;
	}
	else
	{
		tokens[pos].val = ft_calloc(2, sizeof(char));
		if (!tokens[pos].val)
			return (0);
	}
	tokens[pos].val[0] = c;
	(*i)++;
	return (1);
}

static int	handle_delimiter(char *prompt, t_oken *tokens, int *i, int *pos)
{
	while (prompt[*i] == ' ')
		(*i)++;
	if (ft_strchr("<>|", prompt[*i]))
	{
		if (!fill_delimiter(prompt, tokens, i, *pos))
			return (0);
		tokens[*pos].type = red;
		(*pos)++;
	}
	while (prompt[*i] == ' ')
		(*i)++;
	return (1);
}

t_oken	*generate_tokens(char *prompt, int token_num)
{
	int		i;
	int		pos;
	t_oken	*tokens;

	i = 0;
	pos = 0;
	tokens = ft_calloc(token_num + 1, sizeof(t_oken));
	if (!tokens)
		return (NULL);
	while (prompt[i])
	{
		if (ft_strchr("<>| ", prompt[i]))
			if (!handle_delimiter(prompt, tokens, &i, &pos))
				return (free_the_tokens(tokens));
		if (!ft_strchr(" <>|", prompt[i]))
			if (!handle_arg(prompt, tokens, &i, &pos))
				return (free_the_tokens(tokens));
	}
	return (tokens);
}
