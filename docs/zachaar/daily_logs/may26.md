## 26-05 

Small tasks:
---
- [x] Make/use a checker to decide whether program is built in or not.
- [ ] Setup IO/pipes for built in programs. AKA: implement built_in commands when piping
- [x] Make `single_command`, both built in as built out
- [ ] Check for file permissions when reading infiles, writing/appending to outfiles, reading from heredoc.
- [ ] close IO duplicates in child when only single (builtout) command is executed

Medium Tasks:
---
- [ ] Write the heredoc part.  (might be bigger than expected)
- [ ] Retrieve exit status of last child executed when piping (or when forking)

Big Tasks:
---
- [ ] Figure out how to exit the different fails on the execution side.

