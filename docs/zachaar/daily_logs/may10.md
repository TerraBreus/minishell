## 10-05

**Writing down some random thoughts to organize my brain:**
- Need to close file descriptors
- Find a way to read last end for pipe creation. There are three situations:
  - first command (create and write into new pipe).
  - middle command (create and write into new pipe, read from last pipe).
  - last command (read from last pipe).
- Understand what int values a child must return in edge cases/problems
- Find a way to save the return value of last executed child.
