/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conxita.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:31:13 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/03 19:26:30 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

typedef struct s_redirect
{
	int	fd_pipe[2];
	int	aux_fd;
	int	fd;
}				t_redirect;

typedef struct s_parsing
{
	bool			o_simple;
	bool			o_double;
	t_redirect		*redirect;
}				t_parsing;

//Signal Handler
void	signal_hook(int sig);
void	setup_signals(void);

//Prompt Handler
int		handle_prompt(char *prompt);

//Conxita Handler
void	print_conxita(void);

//Bool Utils
void	b_invert(bool *b);
