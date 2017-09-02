/* Simulate a shell with chown and date imbued, and others commands
 * can be executed if the path is specified. */

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

/* Receives a string, which is the command typed in the shell
 * and return a string array according to argv structure. */
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

/* Prints the date in the shell with the same format as the 
 * usual date command. */
void cmd_date() {
    time_t t;
    char *buf = malloc(80 * sizeof(int));
    t = time(&t);

    struct tm* result = malloc(sizeof(struct tm));

    localtime_r(&t, result);
    strftime(buf, 80, "%a %b %d %H:%M:%S %Z %Y", result);
    printf("%s\n", buf);

    free(result);
}

/* Receives the command and its argumments that the shell
 * will execute and execute it. */
void cmd_execute(char* path, char* cmd) {
    char** args = parse_args(cmd);
    pid_t p;
    
    if ((p = fork()) == 0) {
        execv(path, args);
        perror("error executing last command");
    } 

    else {
        waitpid(p, NULL, 0);
        free(args);
    }
}

/* Receives the command typed in the shell, the size of 
 * the current directory string, and the current directory
 * string. Execute the chown command according to the
 * argumments passed at the shell. */
void cmd_chown(char* cmd, int size, char* dir) {
    
    char **args = parse_args(cmd);
    
    // concatenate the local directory and the file name
    char *path_file = calloc(size + strlen(args[2]) + 1, sizeof(char));
    strcpy(path_file, dir);
    strcat(path_file, "/");
    strcat(path_file, args[2]);

    //take ':' from the group name
    int grp_sz = strlen(args[1]) - 1;
    char *grp_name = calloc (grp_sz, sizeof(char));
    for (int i = 0; i < grp_sz; i++) {
        grp_name[i] = args[1][i + 1];
    }

    struct group* gp = getgrnam(grp_name);
    int ret = chown(path_file, -1, gp->gr_gid);
    if (ret == -1)
    	perror("error:chown");

    free(grp_name);
    free(path_file);
}

/* Receives the command typed in the shell and the 
 * current directory and calls the right function for 
 * the typed command. */
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

    else if (strcmp(path, "chown") == 0)
        cmd_chown(cmd, strlen(lc_dir), lc_dir);

    else
        cmd_execute(path, cmd);
}

/* Execute and maintains the shell. */
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
    }
}

int main() {
    input_interface();
    return 0;
}
