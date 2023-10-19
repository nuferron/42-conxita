#include "../../conxita.h"

int	get_word_len(char *prompt, int i)
{
	int	len;

	len = 0;
	while (prompt[i] && prompt[i] != ' ')
	{
		if (prompt[i] == '\'')
			s_quote_len(prompt, &i, &len);
		if (prompt[i] == '"')
			d_quote_len(prompt, &i, &len);
		if (!strchr("'\" <>|", prompt[i]))
			len++;
		i++;
	}
	return (len);
}

void	write_word(char *prompt, t_oken *tokens, int *i, int t_pos)
{
	int	word_len;

	word_len = get_word_len(prompt, *i);
	printf("word_%i: %i\n", t_pos, word_len);
	*i += word_len;
	(void)tokens;
	// tokens[t_pos].val = ft_calloc(word_len, sizeof(t_oken));
	// if (!tokens)
	// 	return (0);//!FREE ALL
	// while (prompt[*i] && prompt[*i] != ' ')
	// {
	// 	if (ft_strchr("'\"", prompt[*i]))
	// 		handle_quotes();
	// 	else
	// 	{
	// 		tokens[t_pos].val = prompt[*i];
	// 		(*i)++;
	// 	}
	// }
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
		if (prompt[*i + 1] == c)
		{
			(*i)++;
			tokens[*pos].val = ft_calloc(3, sizeof(char));
			tokens[*pos].val[1] = c;
		}
		else
			tokens[*pos].val = ft_calloc(2, sizeof(char));
		tokens[*pos].val[0] = c;
		(*i)++;
		(*pos)++;
	}
	while (prompt[*i] == ' ')
		(*i)++;
	(*pos)++;
}

void	populate_tokens(char *prompt, t_oken *tokens)
{
	int	i;
	int	pos;

	i = 0;
	pos = 0;
	if (prompt[0])
		pos++;
	while (prompt[i])
	{
		if (ft_strchr("<>| ", prompt[i]))
			handle_delimiter(prompt, tokens, &i, &pos);
		// if (prompt[i] == '\'' || prompt[i] == '"')
		// 	handle_quotes(prompt, &i);//todo
		// if (!ft_strchr(" <>|", prompt[i]))
		// 	handle_word();//todo
	}
}

void	_populate_tokens(char *prompt, t_oken *tokens)
{
	int	i;
	int	t_pos;

	i = 0;
	t_pos = 0;
	while (prompt[i])
	{
		if (ft_strchr("<>| ", prompt[i]))
			handle_delimiter(prompt, tokens, &i, &t_pos);
		if (!ft_strchr("'\" <>|", prompt[i]))
			write_word(prompt, tokens, &i, t_pos);
		if (prompt[i])
			i++;
	}
}
