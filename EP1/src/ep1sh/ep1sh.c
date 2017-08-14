#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <readline/readline.h>
#include <readline/history.h>

void input_interface () {

    char dir[1024], *s;

    s = getcwd (dir, sizeof(dir) - 1);

    if (s == 0)
        printf ("Error getting pwd: %s\n", dir);
 
    char* str = malloc(sizeof(dir) + 4);
    sprintf(str, "[%s]$ ", dir);
    
    char *line = readline (str);
    if (line && *line)
        add_history(line);

    free(str);
    free(line);
}

int main () {
  
    input_interface();    
    return 0;
}
