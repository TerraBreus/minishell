int	setup_io(t_cmd *c)
{
	static t_pipe	*plumber = NULL;

	if (plumber == null && c->next != null)
	{
		plumber = (t_pipe *)malloc(sizeof(t_pipe));
		if (plumber == null)
			exit(exit_failure);			//todo must be exit_on_malloc_failure.
	}

	//Create the pipe structure if we have more than one command.
	//Check whether we need to create a pipe.
	

	//Set up the pipe according to first, middle or last command.
	//	if first or middle;
	//		Create new pipe.
	//		if last_read_end != -1
	//			set last_read_end to STDIN (which should be -1 if it is the first command.
	//			close last_read_end
	//		set write pipe to STDOUT.
	//		close write pipe.
	//		save last_read_end from the newly created pipe
	//	if last:
	//		if pipe_structure != NULL
	//			set last_read_end to STDIN
	//			close(last_read_end);
	//			set last_read_end to -1
	
	//How can we check what file descriptors we have open?
