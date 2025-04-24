# Built in Commands
Built in means they must effect the shell process. 

For most commands, we will probably need to have an environment variable that handles all the available environment parameters. 

We should be able to add environment parameters so it has to be a dynamic array (possibly a linked list).

They **MUST** be executed in the parent... aka
```c
if (is_builtin(cmd)) {
    execute_builtin(cmd);
} else {
    launch_external_command(cmd);
}
```
Where **ONLY** `launch_external_command(cmd)` would fork to execute.

**Short explanation of commands**
```
cd | Change the current directory
echo | Print text to standard output
pwd | Print current working directory
exit | Exit the shell
env | Print environment variables
export | Add/modify environment variables
unset | Remove environment variables
```

**Possible Prototypes**
FYI: If we want to edit our environment parameter, we must also pass it through the functions (or use our one single global variable, thought we might need that for signals?)

```c
int ft_echo(char **args);
int ft_cd(char **args, t_env *env);
int ft_pwd(void);
int ft_exit(char **args);
int ft_env(t_env *env);
int ft_export(char **args, t_env *env);
int ft_unset(char **args, t_env *env);

```

***(don't forget to free!)*** 
