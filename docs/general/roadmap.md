# ToC
- [Initial display of prompt](./roadmap/display_prompt.md)
- [Tokenizer/input parser/extract input](./roadmap/tokenizer.md)
- [Environment variables handling (copy and editing of char *env[])](./roadmap/environment_variables.md)
- [Built in/absolute Commands](./roadmap/built_in_commands.md)
- [Pipes and redirection operators](./roadmap/pipes_and_redirection.md)
- [History (arrow up down to go through log/previous commands)](./roadmap/history.md)
- [Signal handling (Ctrl-C, Ctrl-D)](./roadmap/signal_handling.md)

Implied everywhere.
- Error handling (exit stati)
	- Errors in child processes should not result in the parent segvaulting or exiting.
