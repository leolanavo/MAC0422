#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "types.h"
#include "cyclist.h"
#include "velodrome.h"

race* r;
barrier* b;
uint interval;
uint timer;
pthread_mutex_t track_lock;

void hold (int lc_continue, cyclist* c) {
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
        
        if (c->lap != c->dist/r->v->length) {
            c->lap++;
            
            if (c->lap >= (r->nlaps - 2) && !r->set_20ms && c->id == r->raffle[0])
                change_speed_90(r, r->raffle[0]);

            else if (c->lap >= (r->nlaps - 1) && !r->set_20ms && c->id == r->raffle[1])
                change_speed_90(r, r->raffle[1]);
            
            else 
                change_speed(c);
        }

        pthread_mutex_lock(&track_lock);
        move_cyclist(c, r->v, r->comp, r->v->length);
        pthread_mutex_unlock(&track_lock);

        hold(local_continue, c);    
    }
    return NULL;
}

void init_race () {
    for (uint i = 0; i < r->ncomp; i++) {
        pthread_create(&r->th_comp[i], NULL, thread_cyclist, (void*)r->comp[i]);
    }
}

/* Construct a race with a velodrome* with length as its length,
 * an array of cyclist* with ncomp as the number of competitors and
 * initialize the number of laps in the race */
race* construct_race (uint length, uint ncomp, uint laps) {
    race* r = malloc(sizeof(race));
    r->comp = construct_competitors(ncomp);
    r->v = construct_velodrome(length);
    r->th_comp = malloc(ncomp * sizeof(pthread_t));
    r->set_20ms = false;
    r->raffle[0] = 0;
    r->raffle[1] = 0;
    r->nlaps = laps;
    r->ncomp = ncomp;
    return r;
}

void sortition (int s[]) {
    s[0] = (int)rand % r->ncomp;
    while (s[1] = (int)rand)
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

    srand(time(NULL));

    interval = 60;
    timer = 0;
    pthread_mutex_init(&track_lock, NULL);
    b = construct_barrier();
    r = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    init_race();
    
    return 0;
}