#include "executor.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int execute_command(char *command, char **args) {
    pid_t pid;
    int status;

    // TODO 1: Fork a child process
    pid = fork();
    if (pid < 0) {
        perror("fork");
        return -1;
    }

    // TODO 2: Child process - Execute the command
    if (pid == 0) {
        // Replace child (target program)
        execvp(command, args);
        perror("execvp");
        exit(1);  
    }

    // TODO 3: Parent process - Wait for child to complete
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        return -1;
    }
    if (WIFEXITED(status)) {
        return WEXITSTATUS(status);
    }
    return -1;
}
