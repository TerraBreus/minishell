# Sources
- [README from chr-ss repo on minishell](https://github.com/Chr-ss/minishell/blob/main/README.md)
- [README from michmos repo on minishell](https://github.com/michmos/42_minishell/blob/main/README.md)
- [Medium article on writing minishell](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

> *The shell basically has two parts, the parsing (where you treat user input), and the execution (where you execute what have been parsed).*

Zachaar is focusing more on execution, Martijn on parsing. However, considering parsing is such a huge and vital part of the program. I reckon it would be best if we both work on the blueprints on how to parse. That way we both have an idea how our input will be processes and what it will process it into so that we both understand what and how to go from there. 

> *I looked up the way bash parses commands*

This is going to be a big thing. How do we parse our input? The idea of linked lists sounds interesting. We could use **enum** to specify what kind of thing (command, pipe, redirection operator, heredoc etc.) it is (but that would mean that prior to that we would have to parse the string to check which kind of enum it is)
- [Big picture/overview of minishell order of execution](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)
- [README from Dimitri-di-silva on Minishell](https://github.com/DimitriDaSilva/42_minishell?tab=readme-ov-file#1-extracting-information)


# Logs
## 22-04

Cleaned up the roadmap file, even though now I believe it should just be on the main README.md of minishell (which it is and sort of makes the roadmap.md file a bit redundant). In these file I hope to create a step by step guide of how what to do and (hopefully) how to do it. 
Could not get as much done cause of distractions. Wanted to further brainstorm and map on the different topics (in the roadmap) but only got round to (more or less) three topics. Expect to continue on this first thing tomorrow morning.

---
## 24-04

**Goals**

- [ ] Finish roadmap.
- [X] Spark Session on Minishell
- [X] Mess around with Tokenizer.

---
## 25-04

Worked on the pipex part:
Made an overarching train of thought that can be filled it with the bits and pieces from my pipex project.
Will want to have my copy pasta meal on a big screen (codam or at parents).

Ik hoop dat het te begrijpen is. Ik berust vooral op het idee dat de linked list van alle commands om uit te voeren (the plumber structure) al in de juiste volgorde zit. Dit will zeggen dat bijvoorbeeld `cat < infile | grep -l 'text' | vim` will result in:
```c
//The current piece (name in code but actual not really logisch)
plumber->data;
	args = ['cat', NULL];
	pipe = ONLY_OUT;
	redirection = ONLY_IN;
plumber->next;
	would lead the the next element.

//Which would have the following data:

args = ['grep', '-l', 'text', NULL];
pipe = IN_OUT;
redirection = NULL;

//The next would then consequently lead to the next element;
// which would have as their plumber->data;

args = ['vim', NULL];
pipe = ONLY_IN;
redirection = NULL;

//And NULL as their plumber->next;
```

I am sure there are still a lot of edgecases I have not seen but as a rough draft I think it can definitely be fruitful.

In some situations the order of execution might not entirely be from left to right:
`echo 'hello' | cat < infile | grep -la 'haha' | cat < infile2 > outfile`
Technically this only makes the last command needed but I believe bash still executes everything (we can check this by adding an unknown command before the last command). Therefore the order would still be from left to right but we would/could constantly have to overwrite the standard I/O, this would be a bit complicated with closing maybe but then again maybe not since we always need to close.

Okay well, that is for next time!

Also realized current stage does not tell difference of built in commands. Before forking we must check whether the command is built in to avoid unneccesary children...

---
## 29-04
**Weekly meetup recap**
The input for execution has more or less been established. 
On the parsing part it is important the initial command line gets parsed/tokenized into the following two structures:
They are both a version of linked lists.
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
---
## 30-04
For today I want to make my notes about the HEREDOC, how to implement it and how to build the necessary structures around it. I do not expect this to take all day so if there is time and energy left at the end of todays session, I would like to take a look at the MAKEFILE and see if we can update it to make future experiences more optimized and streamlined. (adding object directories, having multiple make commands that do (for example) create a minishell that only does the piping part or tests specific parts. AKA creates different programs if needed/specified)

Need to decide where the heredoc gets handled. I believe it should be done between parsing and execution as a sort of 'in between' program.

*Small note: If no EOF is given (`cat <<`) we must get an error. Also, `cat << \n` is really weird in bash...*

Here is what I expect the function to look like:
```c
/*
** If a HEREDOC has been identified, we must (after parsing the rest of the cmdline)
** 1. Read input from the users std_in. (a simple readline command).
** 2. Iterate through the input to check whether the delimiter is present.
** 3. If not, simply store the input in a temporary file (which we must delete at some point!), save the fd and repeat.
** 3. If yes, save everything upo to the delimiter in the buffer/temporary file, free and exit.
**
** so something along the lines of...
*/

int	heredoc(char *delimiter)
{
	int		fd;
	int		len;
	char	*input;

	//I think this should be done before entering the heredoc program but just in case I write it down.
	if (*delimiter== '\0')
		return (-1);

	fd = open(".temp_heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (-1);

	while (1)
	{
		input = readline(">");
		if	(input == NULL)
			break ; //In case of malloc failure, we do not necessarily need to have the whole minishell exit...
		len = ft_strlen(input);
		if (ft_strcmp(input, delimiter) == 0) 
			break ;
		write(fd, input, len);
		write(fd, "\n", 1);
		free(input);
	}
	free(input);
	return (fd);
}
```
