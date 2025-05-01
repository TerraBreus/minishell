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


