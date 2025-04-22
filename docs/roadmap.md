# Sections
- Initial display of prompt
- Tokenizer/input parser/extract input
- Environment variables handling (copy and editing of char *env[])
- Built in/absolute Commands
- Pipes and redirection operators
- History (arrow up down to go through log/previous commands)
- Signal handling (Ctrl-C, Ctrl-D)

Implied everywhere.
- Error handling (exit stati)
	- Errors in child processes should not result in the parent segvaulting or exiting.
