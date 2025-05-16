## 16-05

Rewrote the whole execution side for the past few days.
Haven't been able to compile it but on a structural account it should be (sort of) complete. 

There is a good chance a lot is still wrong with it.
Also I haven't touched the topic of retrieving the childs exit status.
This will also require me to change the code of `exec_cmd()`, as of now it only returns `-1` or `127`.

Also errors are going to be a bitch.
I will constantly have to free, close and return specific values for specific cases.
I have not touched or thought about this too much as of now, mainly trying to get everything 'working'...

Hope to have it compile and realise how much I still lack by tomorrow.
