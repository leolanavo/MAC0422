#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <grp.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <readline/history.h>
#include <readline/readline.h>

char** parse_args(char* str) {
    char** args;
    int k;
    int nspaces = 0, last = 0;

    int* wsizes = calloc(8, sizeof(int));

    for (int i = 0, cur_size = 0; i < strlen(str); i++, cur_size++) {

        // Realloc
        if (nspaces == sizeof(wsizes) / sizeof(int)) {
            int* aux = calloc(2 * nspaces, sizeof(int));
            for (int j = 0; j < nspaces; j++)
                aux[j] = wsizes[j];
            free(wsizes);
            wsizes = aux;
        }

        if (str[i] == 32 || i == strlen(str) - 1) {
            wsizes[nspaces] = cur_size;
            nspaces++;
            cur_size = 0;
            i++;
        }
    }

    args = malloc((nspaces + 2) * sizeof(char*));

    for (int i = 0, j = 0; i < strlen(str) && j < nspaces; i++, j++) {
        args[j] = malloc(wsizes[j]);
        for (k = 0; i < strlen(str) && str[i] != 32; k++, i++)
            args[j][k] = str[i];
        args[j][k] = '\0';
        last = j;
    }

    args[last + 1] = NULL;
    return args;
}

void cmd_date() {
    time_t t;
    char buf[26];
    t = time(&t);

    struct tm* result = malloc(sizeof(struct tm));

    localtime_r(&t, result);
    asctime_r(result, buf);
    printf("%s", buf);

    free(result);
}

void cmd_execute(char* path, char* cmd) {
    char** args = parse_args(cmd);
    pid_t p;
    if ((p = fork()) == 0) {
        execv(path, args);
        perror("deu ruim");
        exit(-1);
    } else {
        waitpid(p, NULL, 0);
        free(args);
    }
}

void cmd_chown(char* cmd, int size, char* dir) {
    // parse de arguments
    int sz_group, offset, tmp;
    offset = 7; // removing "chown :" from the counting

    for (sz_group = offset; sz_group < size && cmd[sz_group] != 32; sz_group++)
        ;
    char* grp_name = calloc(sz_group - offset, sizeof(char));

    tmp = sz_group - 1;
    for (int j = sz_group - offset - 1; tmp >= offset; tmp--, j--)
        grp_name[j] = cmd[tmp];

    int sz_file = size - sz_group - 1;
    char* file_name = calloc(sz_file, sizeof(char));

    tmp = size - 1;
    for (int j = sz_file - 1; tmp >= size - sz_file; j--, tmp--)
        file_name[j] = cmd[tmp];

    // concatenate the local directory and the file name
    char* path_file = calloc(size + sz_file + 1, sizeof(char));
    strcpy(path_file, dir);
    strcat(path_file, "/");
    strcat(path_file, file_name);

    // get the group id
    struct group* grp = getgrnam(grp_name);
    if (grp == NULL)
        printf("There is no such group named '%s'\n", grp_name);
    else {
        int ret_value = chown(file_name, (uid_t)-1, grp->gr_gid);
        if (ret_value == -1)
            printf("chown: erro\n");
    }
}

void process_cmd(char* cmd, char* lc_dir)
{
    /*Get the first string of the command*/
    int i;
    int size = strlen(cmd);

    for (i = 0; i < size && cmd[i] != 32; i++)
        ;
    char* path = calloc(i, sizeof(char));

    for (i = i - 1; i >= 0; i--)
        path[i] = cmd[i];

    if (strcmp(path, "date") == 0)
        cmd_date();

    else if (strcmp(path, "chown") == 0)
        cmd_chown(cmd, size, lc_dir);

    else
        cmd_execute(path, cmd);
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
    }
}

int main()
{
    input_interface();
    return 0;
}
