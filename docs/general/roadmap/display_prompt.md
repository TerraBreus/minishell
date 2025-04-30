# Display prompt
When starting the program, we should get a prompt (with no active history) and the ability to type stuff into the terminal (and store it somewhere).
```
./minishell
minishell>
```
Use a continuous loop (`while (true)`) that exits only on the exit command (and ctrl-D).

Display a *dynamic* (meaning can be changed) prompt (fe: `minishell$`)

Use GNL or readline() to capture input. 
	Using readline has the disadvantage of memory leaks (which we do not have to deal with but I do not like memory leaks so -\_(o_o)_/-). If we use GNL (`char *buffer = get_next_line(0)` should do something similar) we are responsible for our own memory leaks.

Store all registered input in a linked list. I have a hunch some of the system calls can be useful here.
