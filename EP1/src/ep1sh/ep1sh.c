#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

void input_interface () {

    char dir[1024], *s;

    s = getcwd (dir, sizeof(dir) - 1);

    if (s == 0)
        printf ("Error getting pwd: %s\n", dir);
  
    printf("[%s]$ ", dir);
    
    char *line = readline ("");
    if (line && *line)
        add_history(line);

    free(line);
}

int main () {
  
    input_interface();    
    return 0;
}
