#pragma once
#define READLINE_LIBRARY
#include "libs/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <termios.h>
#include <curses.h>
#include <errno.h>
#include <term.h>
#include <tcl.h>
#include <stdbool.h>
#include "libs/readline/readline.h"
#include "libs/readline/history.h"

#define LINE_DEL	"\012"
#define SYNTAX		"syntax error near unexpected token "

enum	e_arg_type {red = 0, arg = 1};
enum	e_output {stdo = 0, opipe = 1};
enum	e_input {stdi = 0, ipipe = 1};
enum	e_chev {std = 0, outt = 1, outa = 2, in = 3, here = 4};

typedef struct s_cmd t_cmd;
typedef struct s_env t_env;
typedef struct s_oken t_oken;
typedef struct s_redir t_redir;

typedef struct s_conxita
{
	t_cmd	*cmd;
	t_env	*env;
	t_oken	*token;
	t_redir	*redir;
	int		exit;
}	t_conxita;

typedef struct s_chev
{
	char		*file;
	int			fd;
	enum e_chev	type;
	void		*prev;
	void		*next;
}	t_chev;

typedef struct s_cmd
{
	char			**cmd;
	t_chev			*chev;
	enum e_output	output;
	enum e_input	input;
	int				len;
	int				last[2];
}	t_cmd;

typedef struct s_redir
{
	int		fd_pipe[2];
	int		fdr_aux;
}	t_redir;

typedef struct s_parsing
{
	bool	o_simple;
	bool	o_double;
	t_cmd	*cmd;
}	t_parsing;

typedef struct s_oken
{
	enum e_arg_type	type;
	char			*val;
}	t_oken;

typedef struct s_env
{
	char	*key;
	char	*value;
	bool	show;
	void	*next;
}	t_env;

/*Signal Handler*/
void	signal_hook(int sig);
void	setup_signals(void);

/*Prompt Handler*/
int		handle_prompt(char *prompt, t_conxita *all);

/*Tokenizer*/
t_oken	*glorified_ft_split(char *prompt, t_conxita *all);
int		get_token_num(char *prompt);
t_oken	*generate_tokens(char *prompt, int token_num);
void	quote_len(char *prompt, int *i, int *len);
void	fill_quotes(char *prompt, t_oken *token, int *i, int *j);
char	*expand_env(t_conxita *all, char *prompt);
int		is_env(char c);
char	*replace_variable(char *str, char *old, char *new);
void	skip_unexpandable(char *str, int *i);

/*Conxita Handler*/
void	print_conxita(void);

/*Utils*/
void	b_invert(bool *b);
char	*ft_strtrim_free(char *s1, char *set);
int		is_builtin(char *str);
int		get_arg_number(char **args);

/*Environment Utils*/
t_env	*search_env(t_env *env, char *key);
char	**env_to_mat(t_env *env, int print);
t_env	*env_to_lst(char **env);
void	env_addback(t_env **env, t_env *new);
t_env	*env_last(t_env *env);
t_env	*new_env(char *env_var);
char	*splitting_env(char *env, int flag);

/*Length Utils*/
int		arg_count(t_oken *token, int start);
int		cmd_count(t_oken *token, int i);
int		env_len(t_env *env);
int		path_count(const char *str, char sep);
int		get_arg_number(char **args);

/*Initializing Utils*/
int		init_cmd_cmd(t_oken *token, t_cmd *cmd, int i, t_env *env);
int		init_cmd_red(t_conxita *all, t_cmd *cmd, int *i);
void	init_pipe(t_cmd *cmd, int is_pipe);
t_redir	*init_redir(void);
int		get_out_fd(t_cmd *cmd);
t_cmd	*cmd_to_null(int len);

/*Path Utils*/
char	*minisplit(char *path, int count);
char	*get_path(t_env *env, char *str);

/*Chevrons Functions*/
t_cmd	*token_to_cmd(t_conxita *all, int len);
int		cmd_count(t_oken *token, int i);
void	chev_addback(t_chev **chev, t_chev *new);
t_chev	*chev_last(t_chev *chev);
t_chev	*new_chev(char *file, char *type);

/*Execution*/
int		lets_execute(t_conxita *all, int len);
int		exec_heredoc(t_cmd *cmd, char *key);
int		here_doc(char *key);
int		ft_waitpid(int pid, int len);
int		redirections(t_cmd *cmd, t_redir *redir);
int		init_chev(t_chev *chev, int	*last);

/*Errors*/
int		print_errors(char *str);

/*Builtins*/
int		builtin_echo(char **args);
int		builtin_pwd(void);
int		builtin_cd(char **args, t_env *env);
int		builtin_exit(char **args, t_conxita *all);
int		builtin_env(t_env *env_lst);
int		builtin_export(char **args, t_env *env_lst);

/*Free*/
void	free_all(t_conxita *all);
void	*free_the_tokens(t_oken *token);
void	free_env(t_env *env);
