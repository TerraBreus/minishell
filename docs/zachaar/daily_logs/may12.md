## 12-05

TODO PRIORITY LIST

- Meditate and become less snoozy
- Close filedescriptors correctly. Most likely this is why we constantly run into problems.

Totally done with this bullshit. Function does not work for shit and I completely lost overview.
readline command did not work properly due to not correctly saving (and restoring) the std io processes (they would be closed indefinitely by all other dup2 calls). Function works "fine" for 1 command however get fuzzy when using multiple commands. I will fix this no matter what, but it will take more time than expected. 
