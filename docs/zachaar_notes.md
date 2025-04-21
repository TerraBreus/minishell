# Sources
- [README from chr-ss repo on minishell](https://github.com/Chr-ss/minishell/blob/main/README.md)
- [README from michmos repo on minishell](https://github.com/michmos/42_minishell/blob/main/README.md)
- [Medium article on writing minishell](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

  *The shell basically has two parts, the parsing (where you treat user input), and the execution (where you execute what have been parsed).*

  *I looked up the way bash parses commands*
  
  This is going to be a big thing. How do we parse our input? The idea of linked lists sounds interesting. We could use **enum** to specify what kind of thing (command, pipe, redirection operator, heredoc etc.) it is (but that would mean that prior to that we would have to parse the string to check which kind of enum it is)
- [Big picture/overview of minishell order of execution](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)

