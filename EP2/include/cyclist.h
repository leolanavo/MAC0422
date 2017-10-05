#ifndef CYCLIST_H
#define CYCLIST_H

/* Change the speed of a cyclist according to the rules defined in
 * the assignment. */
void change_speed (cyclist* c);

/* Change the speed of a cyclist to 90Km/h if the drawn number is
 * smaller than 0.1, this number follow an uniform distribution
 * between 0 and 1 */
void change_speed_90 (cyclist* c);

/* Initialize a cyclist pointer with the standar value of which
 * parameter */
cyclist* init_cyclist ();

/* Change the position of the cyclist in the velodrome matrix */
void position_cyclist (cyclist* c, uint lin, uint row, uint length);

#endif
