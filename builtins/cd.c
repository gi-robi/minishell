#include "../includes/builtins.h"
//acces

static char *pathishome(char **env)
{
    int i;
    char *path;

    path = NULL;
    i = 0;
    while(env[i] != NULL)
    {
        if(ft_strncmp("HOME=", env[i], 5) == 0)
        {
            path = env[i] + 5;
            break;
        }
        i++;
    }
    return(path);
}

static int ft_error(char *path)
{
    if (access(path, F_OK) == -1)
    {
        write(2, "File doesn't exist\n", 19);
        return(-1);
    }
     if (access(path, R_OK) == -1)
    {
        write(2, "Permission to read denied\n", 26);
        return(-1);
    }
     if (access(path, X_OK) == -1)
    {
        write(2, "Permission to execute denied\n", 29);
        return(-1);
    }
    return (0);
}

int cd(char *path, char **env)
{
    if(!path)
        path = pathishome(env);
    if (!path)
    {
        write(2,"HOME is not configured\n", 24);
        return(-1);
    }
    if(ft_error(path) == -1)
        return(-1);
    if (chdir(path) != 0)
    {
        write(2, "chdir failed\n", 13);
        return(-1);
    }
    return(0);
}
int main()
{
    char **command = {"cd", NULL};
    cd(command[1], env);
    pwd();
    return(0);
}