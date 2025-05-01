## 01-05

*Very important ofcourse yes yes. Trying out a github action that automatically adds logs to the main readme file...*
- [x] Use shell script in GitHub actions to automatically update logs on main readme.md

With what little time I have left for the day I would like to fix a small issue with the [current heredoc](./april30.md).

It runs in to the problem of not being able to handle multiple heredocs as the temporary filename will get replace the second time the function gets called.

A simple fix would be to keep a static variable and add it to the filename. Technically not ideal (as we will need to remove the file as well later, so we have to keep track of the filename (or do a bunch of extra work).

Just to keep things light for now, let's try the easy way out:
```c
char	*create_filename()
{
	static int	i = 0;
	char	*addendum;
	char	*filename;

	addendum = ft_itoa(i);
	filename = ft_strjoin("temp_heredoc_", addendum);
	free(addendum);
	i++;
	return (filename);
}
// Don't forget to free later on!
```

I notice now that our redirection structure holds a variable for filename_path. We can, in case of heredoc, simply store the filename under that variable. After the entire command line, we can then simply iterate through the command/redirection structure, check for heredoc and, if yes, delete the filename.
```c
//At end of executing entire command line:

void	delete_heredoc_file(t_command *data)
{
	t_redir		*r_temp;

	while (data != NULL)
	{
		r_temp = data->redirection;

		while (r_temp != NULL)
		{
			if (r_temp->heredoc_fd != -1)
				unlink(r_temp->filename_path); //We could always check if we are not dealing with a null pointer and if the file actually exists (if filename != NULL and f_access(filename, F_OK)). We also need to free but maybe we should do that in a separate function that frees the entire structure.
			r_temp = r_remp->next;
		}
		data = data->next;
	}
}
```
Hope this makes any sense.

With this (temporal) solution, we should be able to finalize the structures needed in order to start writing.

To see the actual structures check [../../../inc/structs.h](../../../inc/structs.h)

---
As a small task, I tried to update the Makefile to have object directory. However, I could not understand Martijns implementation and was too tired to do more research. So I simply asked chatGPT to do it for me. When I tried to make everything, I got compilation errors so no idea if it is working. 

If I fucked up the Makefile, just restore the old version (on the github page you have a history button):
---
![temp](https://github.com/user-attachments/assets/655ac62f-f3db-41e3-a4c5-71132f06d3a7)
