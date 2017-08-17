#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

void process_cmd(char* cmd) {
    /* "/bin/ping -c 10 www.google.com.br"; */
    /* "/bin/usr/cal 2017"; */
    /* "./ep1"; */

    int i;
    int size = strlen(cmd);
    
    for (i = 0; i < size && cmd[i] != 32; i++);
    
    char* path = malloc(i--);
    while(i >= 0) {
        path[i] = cmd[i];
        i--;
    }

    printf("cmd: %d\n", size);
    printf("path: %lu\n", strlen(path));
    printf("your path: %s\n", path);

    free(path);
    path = NULL;
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
        printf("%s\n", line);
        if (line && *line) {
            process_cmd(line);
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
