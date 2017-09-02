/* Simulate a shell with chown and date imbued, and others commands
 * can be executed if the path is specified. */

#ifndef EP1SH_H
#define EP1SH_H

/* Receives a string, which is the command typed in the shell
 * and return a string array according to argv structure. */
char** parse_args(char* str);

/* Prints the date in the shell with the same format as the 
 * usual date command. */
void cmd_date();

/* Receives the command and its argumments that the shell
 * will execute and execute it. */
void cmd_execute(char* path, char* cmd);

/* Receives the command typed in the shell, the size of 
 * the current directory string, and the current directory
 * string. Execute the chown command according to the
 * argumments passed at the shell. */
void cmd_chown(char* cmd, int size, char* dir);

/* Receives the command typed in the shell and the 
 * current directory and calls the right function for 
 * the typed command. */
void process_cmd(char* cmd, char* lc_dir);

/* Execute and maintains the shell. */
void input_interface();
