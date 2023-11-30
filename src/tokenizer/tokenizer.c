#include "../../conxita.h" 

//Prompt tokenizer
t_oken	*glorified_ft_split(char *prompt, t_conxita *all)
{
	int		token_num;
	t_oken	*tokens;

	prompt = ft_strtrim_free(expand_env(all, prompt), " ");
	if (!prompt)
		return (NULL);
	token_num = get_token_num(prompt);
	if (token_num == 0)
		return (NULL);
	tokens = generate_tokens(prompt, token_num);
	free (prompt);
	if (!tokens)
		return (NULL);
	return (tokens);
}
