#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "types.h"
#include "cyclist.h"
#include "velodrome.h"

race* r;
barrier* b; 

void hold (int lc_continue) {
    lc_continue = (lc_continue == 0) ? 1 : 0;
    
    pthread_mutex_lock(&b->lock);
    uint arrived = ++(b->counter);

    if (arrived == r->ncomp) {
        pthread_mutex_unlock(&b->lock);
        b->counter = 0;
        /*Break cyclists here, before next round*/
        b->flag =  lc_continue;
    }

    else {
        pthread_mutex_unlock(&b->lock);
        while (b->flag != lc_continue);
    }
}

void* thread_cyclist (void *arg) {

    int local_continue = 0;
    cyclist* c = (cyclist*) arg;

    while (c->lap < r->nlaps) {
        

        hold(local_continue);    
    }
    return NULL;
}

void init_race () {
    for (uint i = 0; i < r->ncomp; i++) {
        /*Finish initializing the cyclists here*/
        pthread_create(&r->th_comp[i], NULL, thread_cyclist, (void*)r->comp[i]);
    }
}

/* Construct a race with a velodrome* with length as its length,
 * an array of cyclist* with ncomp as the number of competitors and
 * initialize the number of laps in the race */
race* construct_race (uint length, uint ncomp, uint laps) {
    race* r = malloc(sizeof(race));
    r->v = construct_velodrome(length);
    r->comp = construct_competitors(ncomp);
    r->th_comp = malloc(ncomp * sizeof(pthread_t));
    r->nlaps = laps;
    r->ncomp = ncomp;
    return r;
}

barrier* construct_barrier () {
    barrier* b = malloc(sizeof(barrier));
    b->counter = 0;
    b->flag = 0;
    pthread_mutex_init(&b->lock, NULL);
    return b;
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

    b = construct_barrier();
    r = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    init_race();
    
    return 0;
}