#include <stdio.h>
#include <sys/wait.h>
#include <spawn.h>

extern char **environ;

int system(char *cmd)       /* posix_spawn() 함수를 사용 */
{
    pid_t pid;
    int status;
    char *argv[] = {"sh", "-c", cmd, NULL};

    posix_spawn(&pid, "/bin/sh", NULL, NULL, argv, environ);

    waitpid(pid, &status, 0);

    return status;
}

int main(int argc, char **argv, char **envp)
{
    while( *envp)
        printf("%s\n", *envp++);

    system("who");
    system("nocomman");
    system("cal");

    return 0;
}