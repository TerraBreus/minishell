## Notes
- Check for file descriptors. Replace all `close` systemcalls with `ft_close` that prints an error message if `close` returns `-1`.
- also not sure whether heredoc now works. Signals and file descriptors might not be done correcty. It's all a bit vague for me at the moment (`setup_heredoc.c`).
- Do we even use setup_pipe_built_in?

## Norminette
*In order to remove the comments without losing them, they are placed in codeblocks.*
- [X] builtin_cmd.c
   ```c
		if (setup_pipe_builtin(pipe_data, cmd_list->type) == -1)
			exit(EXIT_FAILURE);			//TODO
		if (setup_redir(cmd_list->redirection) == -1)
			exit(EXIT_FAILURE);		//TODO

   ```
- [X] builtout_cmd.c
	```c
		if (pid == -1)
			exit(EXIT_FAILURE);				//TODO Forking failure.
		if (setup_pipe_builtout(pipe_data, pid, cmd_list->type) == -1)
			exit(EXIT_FAILURE);			//TODO dup2 failure.
		if (setup_redir(cmd_list->redirection) == -1)
			exit(EXIT_FAILURE);				//TODO dup2 failure
	```
- [X] check_4_heredoc.c
	```c
		if (setup_heredoc(shell, temp) == -1)
			return (-1);//TODO heredoc handler failed.
	```
- [X] check_file_permissions.c
- [X] child_command.c
- [x] count_commands.c

- [x] create_pipe.c

- [x] exec_cmd.c

- [x] execution.c
	```c
	if (check_4_heredoc(shell, cmd_list) ==  -1)
		exit(EXIT_FAILURE); //TODO Just print an error message and make sure setup_redir does not segvault.
	```
- [x] ft_wait.c

- [x] internal_error.c

- [x] is_built_in.c

- [x] mult_cmd.c

- [x] parse_mult_cmd.c

- [x] redirection_handlers.c
	```c
	if (fd_in ==  -1)
		return (-1); //Would be useful to print error message of strerrno;
	```
- [x] save_close_restore_io.c

- [x] setup_heredoc.c
	```c
	if (pipe(pfd) ==  -1)
		exit(EXIT_FAILURE); //TODO
	if (pid ==  -1)
		exit(EXIT_FAILURE); //TODO Forking failure.
	```
- [x] setup_pipe_builtin.c

- [x] setup_pipe_builtout.c
	```c
	if (dup2(pipe_write, STDOUT_FILENO) ==  -1)
		exit(EXIT_FAILURE); //TODO dup2 failure. Close pipes etc.
	if (dup2(lre, STDIN_FILENO) ==  -1)
		exit(EXIT_FAILURE); //TODO
	if (dup2(lre, STDIN_FILENO) ==  -1)
		exit(EXIT_FAILURE); //TODO
	```
- [x] setup_redir.c

- [x] single_cmd.c
	```c
	if (pid ==  -1)
		exit(EXIT_FAILURE); //TODO
	```
