/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   included_libs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: masmit <masmit@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:48:09 by masmit            #+#    #+#             */
/*   Updated: 2025/04/22 15:48:10 by masmit           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDED_LIBS_H
# define INCLUDED_LIBS_H

# include "minishell.h"

/* Personal libft */
# include "libft.h"

/* Standard I/O functions (printf, perror) */
# include <stdio.h>

/* Memory management (malloc, free) */
# include <stdlib.h>

/* POSIX API (write, access, open, read, close, unlink, etc.) */
# include <unistd.h>

/* File control options (open flags, etc.) */
# include <fcntl.h>

/* Process types (pid_t, etc.) */
# include <sys/types.h>

/* File status (stat, fstat, lstat) */
# include <sys/stat.h>

/* Process waiting (wait, waitpid, wait3, wait4) */
# include <sys/wait.h>

/* Terminal I/O control (ioctl, tcsetattr, tcgetattr) */
# include <sys/ioctl.h>

/* Signal handling (signal, sigaction, sigemptyset, sigaddset, kill) */
# include <signal.h>

/* Directory operations (opendir, readdir, closedir) */
# include <dirent.h>

/* String operations (strerror) */
# include <string.h>

/* Error numbers (errno) */
# include <errno.h>

/* Terminal I/O (ttyname, ttyslot, isatty) */
# include <termios.h>

/* Curses/terminal screen handling (base for termcap) */
# include <curses.h>

/* Termcap database (tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs) */
# include <term.h>

/* Readline library (readline, rl_clear_history, rl_on_new_line, etc.) */
# include <readline/readline.h>

/* Readline history management (add_history) */
# include <readline/history.h>

extern int	g_signal;

#endif