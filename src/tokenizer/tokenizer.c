#include "../../conxita.h" 

//Prompt tokenizer
t_oken	*glorified_ft_split(char *prompt, char **env)
{
	int		i;
	int		token_num;
	t_oken	*tokens;

	i = 0;
	prompt = ft_strtrim_free(expand_env(env, prompt), " ");
	if (!prompt)
		return (NULL);
	printf("%s\n", prompt);
	token_num = get_token_num(prompt);
	tokens = ft_calloc(token_num + 1, sizeof(t_oken));
	if (!tokens)
		return (NULL);
	populate_tokens(prompt, tokens);
	free (prompt);
	while (i < token_num)
	{
		printf("%i. [%s]\n", i, tokens[i].val);
		free(tokens[i].val);
		i++;
	}
	free(tokens);
	return (NULL);
}
