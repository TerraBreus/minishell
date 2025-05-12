## 12-05

TODO PRIORITY LIST

- Meditate and become less snoozy
- Close filedescriptors correctly. Most likely this is why we constantly run into problems.

**FINAL WORDS**
Unfortunately, the execution side is a little harder than expected. 
I realized we need to keep track of pipes much more precise and close all file descriptors we don't need. 
The unneccesary file descriptors differ from child to parent and even in these two distinctions is there a difference whether it is the first command, a middle command, or the last command. 

I wrote the workflow down on a piece of paper carefully keeping track of all the file descriptors the process could have and which ones it actually needs. 
This gave me some overview and I tried to put it down in pseudocode. 
Hopefully I can still follow this tomorrow and implement this into actual syntax.

The main problem I dealt with today was the fact that STD\IN and STD\_OUT are two processes you don't want to close if you want to have a continious interaction with the user. 
Thus when I call `dup2(pfd[1], STDOUT_FILENO)` I close the process of STDOUT. 
In the child this is permitted as soon the function called will take over the whole process (Note that this is a different process as the STDIN/OUT processes. I lack a better word for those "processes"). 
However, if we do this in the parent, we run into the trouble of "cutting off" our connection with the user. STDIN\_FILENO will (if done incorrectly) now point towards the read side of the pipe instead of the terminal in which the user is interacting with the program.

The same will happen with redirection operators. This means that redirection must only happen in the child. 


Another work around is to dupe the STDIN and STDOUT processes (`stdin_copy = dup(STDIN_FILENO)`). 
This is no doubt easier yet I am not sure if this will work completely as desired.
The other (probably harder) way shows a much deeper understanding of how file descriptors (and their underlying processes) work and will probably be preferred when debugging.


Finally, piping cannot happen in "the child" when we are dealing with built in commands (since we are not allowed to fork). 
So come to think of it, we will have to use the easy way out either way... 


It seems like I did not think this through but I got a lot wiser. 
I think I will still continue with my initial method and write a different piping/redirection set when we are dealing with build in commands. 
