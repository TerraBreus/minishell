## 05-05

> Where we left of last time:

```c
int	main_pipex(t_cmd *cmd_line)
{
	while (cmd_line != NULL)
	{
		if (cmd_line->next != NULL)
			create_pipe();
		if (cmd_line->cmd != NULL)
		{
			if (cmd_is_built_in(cmd_line->cmd))
				cmd_in_parent(cmd_line);
			else
				cmd_in_child(cmd_line);
		}
		else
			only_redirection(cmd_line->rediriction);
		cmd_line = cmd_line->next;
	}
}
```

As far as I can currently see there are three situations per command block:
- A built in command -> Redirect I/O and execute command without forking.
- A non-built in command -> Redirect I/O and execute command in child.
- A non-command -> Only redirect I/O. No command to execute.

All three of these functions could use the redirection function:
```c
int	my_redirect(t_redir *redir_data)
{
	static t_redir_handler handlers[] = {
		handle_in,
		handle_out,
		handle_append,
		handle_heredoc
	};

	while (redir_data != NULL)
	{
		// set up IO according to type:
		if (redir_data->type < 0 || redir_data->type > 3)
			return (-1);
		if (handlers[redir_data->type](redir_data) == -1)
			return (-1);
		redir_data->next = redir_data;
	}
	return (0);
}
```

> The handler definition would point to the corresponding function:
```c
int	handle_in(t_redir *r)
{
	int		fd_in;

	fd_in = open(r->filename_path, RD_ONLY);
	if (fd_in == -1)
		return (-1);	//Would be useful to print error message of strerrno;
	if (dup2(fd_in, STDIN_FILENO) == -1)
		return (-1);
	close(fd_in);
	return (0);
}

int	handle_out(t_redir *r)
{
	int		fd_out;

	fd_out = open(r->filename_path, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd_out == -1)
		return (-1);
	if (dup2(fd_out, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_out);
	return (0);
}

int	handle_append(t_redir *r)
{
	int		fd_append;

	fd_append = open(r->filename_path, O_WRONLY | O_CREAT, 0777);
	if (fd_append == -1)
		return (-1);
	if (dup2(fd_append, STDOUT_FILENO) == -1)
		return (-1);
	close(fd_append);
	return (0);
}

int handle_heredoc(t_redir *r)
{
	if (dup2(r->heredoc_fd, STDIN_FILENO) == -1)
		return (-1);
	close(heredoc_fd);
	return (0);
}
```

Thus we would go through the redirection (linked) list and constantly overwrite the I/O.
