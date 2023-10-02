/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conxita.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blvilarn <blvilarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 14:31:13 by blvilarn          #+#    #+#             */
/*   Updated: 2023/10/02 20:04:21 by blvilarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libs/libft/libft.h"
// #include "libs/readline/readline.h"
// #include "libs/readline/history.h"
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
#include <readline/readline.h>
#include <readline/history.h>

//Signal Handler
void	signal_hook(int sig);
void	setup_signals(void);

//Prompt Handler
int		handle_prompt(char *prompt);
