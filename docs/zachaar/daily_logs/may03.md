## 03-05
### Mapping out today's session:
Simply put, I want to make a big start on the execution part for piping and redirecting etc.

As an overarching idea, I want to first have it work simply by itself, without the actual main. Thus I will use a (temporary) main and makefile and will integrate it into the minishell later on. 

This way I can test the thing by itself without having to worry about possible leaks/errors in the parsing.

On another note, I should really get into the whole 'git branches' cause currently pushing is a bit tedious (and not rewarding) when we are working on the project at the same time.

*Oh, also on a personal level. I want to check my calendar to get an idea of next week and download some youtube videos for at home :) This I can do at the end, but writing them down as to not forget.*

---
Summarized, this is my plan for today.

- [ ] **Main objective:** Lay out foundation for operation.
- [ ] *Optional:* Work on a git branch.
- [ ] *Personal:* Check calendar for next week and download some youtube videos.
- [ ] *Personal:* Check mail...

Let's see how far we get!

Execution
---
Once more, the structures we will be using.
```c
typedef enum e_redir_type
{
	IN,
	APPEND,
	OUT,
	HEREDOC
}	t_redir_type;

typedef struct s_redir
{
	int				heredoc_fd;
	t_redir_type	type;
	char			*filename_path;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmd
{
	char			**argv;
	t_redir			*redirection;
	pid_t			pid;
	struct s_cmd	*next;
}					t_cmd;
```

In general, I presume the workflow of the execution to go as such.

> First we must figure out the amount of commands/pipes we will be executing/creating.
Thus iterate through the command list.
```c
//We could parse by reference but since I want to edit some pointers and then discard them,
//I figured simply making a copy is wiser.
int	get_cmdc(t_cmd data)
{
	int		cmd_c;

	cmd_c = 1;							// We must have at least one command (structure)
	while (data.next != NULL)
	{
		cmd_c++;
		data = *(data.(next));
	}

	return (cmd_c);
}
```

The amount of pipes we must create have to be equal to `argc - 1`. There is no way around this since we are not doing the bonus part (thus the only way you can have multiple commands is if you are piping them).

>Now that we know how many commands/pipes we will create we can pipe, fork, setup_IO and execute accordingly.
*While writing I realise we will need the environment parameter for the build in commands as well! Also, maybe the cmd_c is irrelevant...*
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
