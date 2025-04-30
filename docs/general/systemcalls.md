# About
This file is to understand and explain the systemcalls allowed for the minishell project. A small explanation and its relevance to the project is given.
# Systemcalls
- readline(char *prompt)
	Reads a line from the standard input. Useful for reading the users input. A (protected) prompt can be displayed to the user.
	**The line returned is malloced and must be free'd manually!**
- rl_clear_history
	Clears the history.
- rl_on_new_line
- rl_replace_line
- rl_redisplay
- add_history(char *str)
	Adds the pointer/string to the history.
- printf
	ft_printf but better.
- malloc
	You should know this by now...
- free
- write
	Write to a specific file descriptor (which can also be STD_IN/STD_OUT).
- access
- open(const char *path, int flag)
	Opens a specific file. Function must know under what conditions to open the file (Read only, write only etc.)
- read(int fd, void *buf, size_t n_bytes)
	Will (try to) read n_bytes from the file descriptor and put them into the buffer. Function returns the amount of bytes read (or -1 in case of error)
- close(int fd)
	Closes the file descriptor. Returns -1 in case of error.
- fork
	Forks the current process. Returns the process id of the child created to the parent. Returns 0 to the child.
- wait
	Wait for a process to finish
- waitpid
	Wait for a specific process to finish (wait for process ID)
- wait3
- wait4
- signal
- sigaction
- sigemptyset
- sigaddset
- kill
- exit
- getcwd
	Returns the current working directory.
- chdir
- stat
- lstat
- fstat
- unlink
- execve(char *path)
	Replaces the current process with the one of the pathname (if it exists). Has a return value of -1 only in case of error. AKA does not return 
- dup 
- dup2(int fd1, int fd2)
	Duplicates the first file descriptor into the second file descriptor.
		dup2(some_fd, STD_IN); means, everything written to STD_IN will now also be written to some_fd.
- pipe(int fd[2])
	Needs two file descriptors. Creates a pipe.
- opendir
- readdir
- closedir
- strerror
- perror
- isatty
- ttyname
- ttyslot
- ioctl
- getenv
- tcsetattr
- tcgetattr
- tgetent
- tgetflag
- tgetnum
- tgetstr
- tgoto
- tputs
