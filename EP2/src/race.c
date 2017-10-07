#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "types.h"
#include "cyclist.h"
#include "velodrome.h"

race* race;
uint th_continue;
pthread_mutex_t inc_count_s0, inc_count_s1, move_cyclist;


uint barrier (uint st) {

    if (st) {
            
        pthread_mutex_lock(&inc_count_s0);
        th_continue_s0++;
        pthread_mutex_unlock(&inc_count_s0);

        while (th_continue != race->ncomp);
        return false;
    }

    else {
            
        pthread_mutex_lock(&inc_count_s1);
        th_continue_s1++;
        pthread_mutex_unlock(&inc_count_s1);

        while (th_continue_s1 != 0);
        return true;
    }
}

void* thread_coordinator (void *arg) {

}

void* thread_cyclist (void *arg) {

    cyclist* c = (cyclist*) arg;
    bool stage = true;

    while (c->lap < race->nlaps) {
        

        overtook(c->lap);
        stage = barrier(stage);     
    }
}

/* Construct a race with a velodrome* with length as its length,
 * an array of cyclist* with ncomp as the number of competitors and
 * initialize the number of laps in the race */
race* construct_race (uint length, uint ncomp, uint laps) {
    race* r = malloc(sizeof(race));
    r->v = construct_velodrome(length);
    r->comp = construct_competitors(ncomp);
    r->laps = laps;
    r->ncomp = ncomp;
    return r;
}

/* Free the race* and its fields */
void destroy_race (race* r) {
    destroy_velodrome(r->v);
    destroy_competitors(r->comp, r->ncomp);
    free(r);
}

int main (int argc, char** argv) {
    if (argc != 4) {
        printf("Insufficient number of arguments\n");
        exit(-1);
    }

    pthread_mutex_init(&inc_count_s0, NULL);
    pthread_mutex_init(&inc_count_s1, NULL);
    pthread_mutex_init(&move_cyclist, NULL);

    th_continue = 0;
    race = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    
    destroy_race(race);
    return 0;
}