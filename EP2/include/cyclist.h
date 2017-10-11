#ifndef CYCLIST_H
#define CYCLIST_H

void adequate_speed(int id, race* r);

/* Change the speed of a cyclist according to the rules defined in
 * the assignment. */
void change_speed (int id, race* r);

/* Change the speed of a cyclist to 90Km/h if the drawn number is
 * smaller than 0.1, this number follow an uniform distribution
 * between 0 and 1 */
void change_speed_90 (race* r);

/* Initialize a cyclist pointer with the standar value of which
 * parameter */
cyclist* init_cyclist (int id);

bool break_cyclist (cyclist* c, race* r);

int has_cyclist (LinkedList* l);

/* Change the position of the cyclist in the velodrome matrix */
void position_cyclist (cyclist* c, int lin, int row, int length);

void move_cyclist (cyclist* c, race* r);

#endif
