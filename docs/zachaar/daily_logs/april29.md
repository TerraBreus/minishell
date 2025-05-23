## 29-04
**Weekly meetup recap**
The input for execution has more or less been established. 
On the parsing part it is important the initial command line gets parsed/tokenized into the following two structures:
They are both a version of linked lists.
### My structs. {#prototype-struct-piping}
```c
struct s_cmd
{
	char **argv; 			//Holds the command and flags. Can be NULL if no command is present (f/e "> out > out2" This will just create the file out and out2)
	t_redir	*redirection;	//Holds the relevant information about I/O operators. Again, NULL if not applicable.
	struct s_cmd	*next;	//Holds the next command to be executed, which can also be used for execution to notify a pipe must be created. (NULL if no other)
} typedef t_cmd;

struct s_redir
{
	int	heredoc_fd;			//Holds fd of the heredoc part. -1 if irrelevant.
	enum redir_type;		//IN/HEREDOC/OUT/OUT_APPEND
	char	*filename_path;	//Relevant only for IN/OUT/OUT_APPEND. The filename/path to be opened.
	struct s_redir	*next;
} typedef t_redir;
```
### Someone elses structs...
> *as of writing Martijn sends the following structure prototype*
```c
typedef struct t_redirect t_redirect;

struct t_redirect
{
    e_redir_type    type;
    char            *file;
    int                in_fd;
    int                out_fd;
    char            *heredoc_delim;
    bool            expand_in_heredoc;
    t_redirect        *next;
};


typedef struct t_command t_command;


struct t_command
{
    bool            has_command;
    bool            has_redirects;		//What if both has_command and has_redirects are false? Perhaps this should be handled in parsing and is not relevant for execution.
    char            *name;				//What is the difference between name and argv? Or is name just argv[0] for readability.
    size_t            argc;				//Would this be the same for every node in the list or is it the iterator? (i = 0, i = 1 , i = 2 etc..)
    char            **argv;
    pid_t            pid;
    t_redirect        *redirects;
    t_command        *next;
};
```

...A definite prototype has yet to be established. This should be done ASAP as it allows Martijn to know what the desired end result is for parsing and it allows Zachaar to start on the execution.
The last codeblock is probably better, however before I can fully understand it, I must first understand how to do the HEREDOC.

Thus the following goals have been set:
- [ ] Understand how to actualize the HEREDOC.  **ETA: 02-05**
- [ ] Write the finalized, desired structures.	**ETA 02-05**
- [ ] Write the execution.						**ETA 10-05**

