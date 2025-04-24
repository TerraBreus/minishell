# Sources
- [README from chr-ss repo on minishell](https://github.com/Chr-ss/minishell/blob/main/README.md)
- [README from michmos repo on minishell](https://github.com/michmos/42_minishell/blob/main/README.md)
- [Medium article on writing minishell](https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218)

> *The shell basically has two parts, the parsing (where you treat user input), and the execution (where you execute what have been parsed).*

Zachaar is focusing more on execution, Martijn on parsing. However, considering parsing is such a huge and vital part of the program. I reckon it would be best if we both work on the blueprints on how to parse. That way we both have an idea how our input will be processes and what it will process it into so that we both understand what and how to go from there. 

> *I looked up the way bash parses commands*

This is going to be a big thing. How do we parse our input? The idea of linked lists sounds interesting. We could use **enum** to specify what kind of thing (command, pipe, redirection operator, heredoc etc.) it is (but that would mean that prior to that we would have to parse the string to check which kind of enum it is)
- [Big picture/overview of minishell order of execution](https://whimsical.com/minishell-architecture-big-picture-7b9N8PL3qHrddbs977mQ2J)
- [README from Dimitri-di-silva on Minishell](https://github.com/DimitriDaSilva/42_minishell?tab=readme-ov-file#1-extracting-information)


# Logs
22-04

Cleaned up the roadmap file, even though now I believe it should just be on the main README.md of minishell (which it is and sort of makes the roadmap.md file a bit redundant). In these file I hope to create a step by step guide of how what to do and (hopefully) how to do it. 
Could not get as much done cause of distractions. Wanted to further brainstorm and map on the different topics (in the roadmap) but only got round to (more or less) three topics. Expect to continue on this first thing tomorrow morning.

24-04

**Goals**

- [ ] Finish roadmap.
- [ ] Spark Session on Minishell
- [ ] Mess around with Tokenizer.

