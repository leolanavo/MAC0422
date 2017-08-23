#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <grp.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

char** parse_args (char* str) {
    int cmd_index;
    int j = 0;
    int nrow = 8;
    int ncol = 8;
    char** args;
    int nspaces = 0;

    int* wsizes = calloc(8, sizeof(int));

    for (int i = 0, cur_size = 0; i < strlen(str); i++, cur_size++) {
        if (str[i] == 32) {
            wsizes[nspaces] = cur_size;
            nspaces++;
            cur_size = 0;
        }
    }
    args = malloc(nspaces * sizeof(char*));

    for (int i = wsizes[0] + 2, j = 1; i < strlen(str) && j < nspaces; i++, j++) {
        args[j - 1] = malloc(wsizes[j]);
        while (i < strlen(str) && str[i] != 32) {
            args[j - 1][i - wsizes[0] - 2] = str[i];
            i++;
        }
    }
}

void cmd_date() {
    time_t t;
    char buf[1024];
    t = time(&t);

    struct tm* result = malloc(sizeof(struct tm));

    localtime_r(&t, result);
    asctime_r(result, buf);
    printf("%s", buf);

    free(result);
}

void cmd_ping(char* path, char* cmd) {
    pid_t p;
    if ((p = fork()) == 0) {
        return;
    }
    else
        return;
}

void cmd_cal(char* path, char* cmd) {

}

void cmd_ep1(char* path, char* cmd) {

}

void cmd_chown (char* path, char* cmd) {

}

void process_cmd(char* cmd, char* lc_dir) {
    /*Get the first string of the command*/
    int i;
    int size = strlen(cmd);

    for (i = 0; i < size && cmd[i] != 32; i++);
    char* path = calloc(i, sizeof(char));

    for (i = i - 1; i >= 0; i--)
        path[i] = cmd[i];

    if (strcmp(path, "date") == 0)
        cmd_date();

    if (strcmp (path, "") == 0)
        cmd_chown(path, cmd);

    else if (strcmp(path, "/bin/ping") == 0)
        cmd_ping(path, cmd);
    
    else if (strcmp(path, "/usr/bin/cal") == 0)
        cmd_cal(path, cmd);
    
    else if (strcmp(path, "./ep1") == 0)
        cmd_ep1(path, cmd);

}

void input_interface() {
    char dir[1024], *s;

    while (1) {
        s = getcwd(dir, sizeof(dir) - 1);

        if (s == 0)
            printf("Error getting pwd: %s\n", dir);

        char* str = malloc(sizeof(dir) + 4);
        sprintf(str, "[%s]$ ", dir);

        char* line = readline(str);

        if (line && *line) {
            process_cmd(line, dir);
            add_history(line);
        }

        free(str);
        free(line);
    }
}

int main() {
    input_interface();
    return 0;
}
