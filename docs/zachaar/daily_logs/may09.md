## 09-05

Implemented very basic functionality of execution part. Current version is on origin/execution branch (`git checkout -b origirin/execution`) and still very unstable but demonstrates the basic functionality of the execution side.

As of now, functionality is restricted to only redirection and single commands. Pipes // Multiple commands have not been implemented. T

TO DO
- Found a bug with the line `"hello" >> infile` which should result into `command "hello" not found` but as of now infinitely loops. Will get into this later.
- Program does not check whether outfile/infile has correct permission.
