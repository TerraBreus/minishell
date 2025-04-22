# Sections
- Initial display of prompt
	- Copy environment list.
 	- init_shell() -> print prompt (msh> to FILED_STDOUT)
	- Wait/read input
- Tokenizer/input parser/extract input
	- Check for quotes -> if quotes, check for the dollar sign ($) -> dollar sign should specify a parameter (f.e $? or $PWD)
	- Split input according to whitespace (except for parameters and quotes)
	- Check what input is and set token accordingly (build in command/relative command(path to cmd)/redirection operator/...)
- Environment variables handling (copy and editing of char *env[])
	- Ability to remove or add parameters to the environment variable
- Built in/absolute Commands
	- echo (-n), cd, pwd, export, unset, env, exit (don't forget to free!) 
- Pipes and redirection operators
- Error handling (exit stati)
	- Errors in child processes should not result in the parent segvaulting or exiting.
- History (arrow up down to go through log/previous commands)
	- All input read via GNL from std_in should be stored in a linked list and be brought back with arrow keys to std_in (where user would type their command).
		This means we must also read for arrow keys yet not actually store them? They might also be just different types of signals that do something
- Signal handling (Ctrl-C, Ctrl-D)
	- No idea how to handle this honestly.

 
 suggestion place for roadmap,
divided in sets of 10 days for a total of 45

first 10 days

R: Read line
E: Eval line syntax
P: Print line
L: loop to return prompt

exit to exit

signals to cancel/kill

Documentation list:
https://www.gnu.org/software/bash/manual/bash.html
	GNU bash manual

https://www.geeksforgeeks.org/signals-c-language/
	signals for interuptions

https://pubs.opengroup.org/onlinepubs/009696599/utilities/xcu_chap02.html
	Tokenizing Guide

https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218
	42 student guide to building minishell

Tokenizing basics, shaping node for linked list


-----------------------------------
second half of first week

Simple commands, ls, pwd, fork, execve

handle command not found, edge cases implementation or wait to end
