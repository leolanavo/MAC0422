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

    // debug
    printf("check path: %s\n", path);
    time_t t;

    if (strcmp(path, "date") == 0) {
        t = time(&t);
        printf("%lu\n", t);
    }


    /*Date command*/
    /* if (strcmp(path, "date") == 0) { */
        /* struct tm* br = malloc(sizeof(struct tm)); */
        /* time_t brtime; */
        
        /* brtime=time(&brtime); */
        /* printf("%lu", brtime); */
        /* br = localtime_r(&brtime, br); */
        /* char* time = asctime(br); */

        /* int str_len = strlen(time); */
        /* char* str_time = calloc(str_len + 2, sizeof(char)); */
        /* for (int j = 0; j < str_len - 6; j++) */
            /* str_time[j] = time[j]; */

        /* printf("%s %d\n", str_time, br->tm_year + 1900); */

        /* free(br); */
        /* free(str_time); */
    /* } */

    /* Chown command */
    /* else if (strcmp(path,"chown") == 0) { */

    /* [> Parsing the string <] */

    /* int sz_group, offset, tmp; */
    /* offset = 7; [> removing "chown :" from the counting <] */

    /* for (sz_group = offset; sz_group < size && cmd[sz_group] != 32;
     * sz_group++);     */
    /* char *grp_name = calloc(sz_group - offset, sizeof(char)); */

    /* tmp = sz_group - 1;        */
    /* for (int j = sz_group - offset - 1; tmp >= offset; tmp--, j--) */
    /* grp_name[j] = cmd[tmp]; */

    /* int sz_file = size - sz_group - 1; */
    /* char *file_name = calloc (sz_file, sizeof(char)); */

    /* tmp = size - 1; */
    /* for (int j = sz_file - 1; tmp >= size - sz_file; j--, tmp--) */
    /* file_name[j] = cmd[tmp]; */

    /* char *path_file = calloc (size + sz_file, sizeof(char)); */

    /* [> Making system call <] */

    /* struct group *grp = getgrnam (grp_name); */
    /* if (grp == NULL) printf("There is no such group named '%s'\n", grp_name);
     */

    /* int rc = syscall(SYS_chown, file_name, (uid_t)-1, grp->gr_gid); */
    /* if (rc == -1) printf("System call failed.\n"); */

    /* else { */
    /* int ret_value = chown (file_name, (uid_t)-1, grp->gr_gid); */
    /* if (ret_value == -1) printf("chown: erro\n"); */
    /* } */
    /* } */
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
