#pragma once
#define READLINE_LIBRARY
#include "libs/libft/libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/ioctl.h>
#include <termios.h>
#include <curses.h>
#include <errno.h>
#include <term.h>
#include <tcl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "libs/readline/readline.h"
#include "libs/readline/history.h"

#define LINE_DEL "\033[A"

enum	e_arg_type {unk = 0, file = 1, red = 2, arg = 3, \
	s_quote = 4, d_quote = 5, cmd = 6, spc = 7};

typedef struct s_cmd
{
	char	**cmd;
	char	*arg;
	int		fd_pipe[2];
	int		fdr_aux;
	int		std[2];
}	t_cmd;

typedef struct s_parsing
{
	bool	o_simple;
	bool	o_double;
	bool	heredoc;
	char	*eof;
	bool	re_input;
	bool	re_output;
	int		append;
}	t_parsing;

typedef struct s_comp
{
	enum e_arg_type	type;
	char			*val;
}	t_comp;

//Signal Handler
void		signal_hook(int sig);
void		setup_signals(void);

//Prompt Handler
int			handle_prompt(char *prompt);
t_comp		*glorified_ft_split(char *prompt);
void		handle_quotes_len(char *prompt, int *i, int *len);
int			get_comp_num(char *prompt);
int			get_word_len(char *prompt, int i, char *delimiters);
void		handle_single(char *prompt, t_comp *comps, int *i, int *comp_i);
void		write_word(char *prompt, t_comp *comps, int	*i, int *comp_i);
void		write_single(t_comp *comps, int *i, char c, enum e_arg_type type);

//Conxita Handler
void		print_conxita(void);

//Bool Utils
void		b_invert(bool *b);

// Chevrons Functions
int			here_doc(t_cmd *cmd, char *key);
int			open_chev(t_cmd *cmd);
int			close_chev(t_cmd *cmd, int append);
