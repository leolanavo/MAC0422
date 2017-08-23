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

void cmd_date() {
    time_t t;
    char buf[1024];
    t = time(&t);

    struct tm* result = malloc(sizeof(struct tm));

    localtime_r(&t, result);
    asctime_r(result, buf);
    printf("%s", buf);
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
}

void input_interface()
{
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

int main()
{
    input_interface();
    return 0;
}
