# Sections
- Initial display of prompt

- Tokenizer/input parser/extract input
	- Check for quotes -> if quotes, check for the dollar sign ($) -> dollar sign should specify a parameter (f.e $? or $PWD)
	- Split input according to whitespace (except for parameters and quotes)
	- Check what input is and set token accordingly (build in command/relative command(path to cmd)/redirection operator/...)
- Environment variables handling (copy and editing of char *env[])
	- Ability to remove or add parameters to the environment variable
- Built in/absolute Commands
- Pipes and redirection operators
- Error handling (exit stati)
	- Errors in child processes should not result in the parent segvaulting or exiting.
- History (arrow up down to go through log/previous commands)
- Signal handling (Ctrl-C, Ctrl-D)
	- No idea how to handle this honestly.
