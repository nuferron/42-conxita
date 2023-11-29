#include "../../conxita.h" 

//Prompt tokenizer
t_oken	*glorified_ft_split(char *prompt, t_env *env)
{
	int		token_num;
	t_oken	*tokens;

	prompt = ft_strtrim_free(expand_env(env, prompt), " ");
	if (!prompt)
		exit((unsigned char)print_errors(NULL));
	token_num = get_token_num(prompt);
	if (token_num == 0)
		return (NULL);
	tokens = generate_tokens(prompt, token_num);
	free (prompt);
	if (!tokens)
		exit((unsigned char)print_errors(NULL));
	return (tokens);
}
