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

If this works, I prefer [my own written structure](./29_04.md#prototype-struct-piping). We could add the process ID (pid) to the s_cmd structure for neatness and perhaps (although unnecessary) the exit code.

**ALSO!!!! THis does not work for multiple here_docs, which we do have to handle... Thus the program will need some tinkering**
