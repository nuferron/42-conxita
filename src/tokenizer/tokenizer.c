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
	token_num = get_token_num(prompt);
	tokens = generate_tokens(prompt, token_num);
	free (prompt);
	if (!tokens)
		return (NULL);
	while (i < token_num)
	{
		printf("tokenizer: %i. [%s]", i, tokens[i].val);
		if (tokens[i].type == red)
			printf (" [red]");
		printf("\n");
		i++;
	}
	return (tokens);
}
