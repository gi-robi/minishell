#include "../../../includes/mini.h"

int ft_pwd(void)
{
    char *cwd;
    cwd = getcwd(NULL, 0);
    if (!cwd)
    {
        perror("getcwd() error");
        return (2);
    }
    printf("%s\n", cwd);
    free(cwd);
    return (0);
}
