# Built in Commands
Built in means they must effect the shell process. 

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
