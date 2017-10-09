#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "types.h"
#include "cyclist.h"
#include "velodrome.h"
#include "linkedlist.h"
#include "scoreboard.h"

race* run;
barrier* b;
//uint interval;
//uint timer;
pthread_mutex_t track_lock;

void hold (int lc_continue, cyclist* c) {
    lc_continue = (lc_continue == 0) ? 1 : 0;
    
    pthread_mutex_lock(&b->lock);
    uint arrived = ++(b->counter);

    if (arrived == run->ncomp) {
        printf("final holder\n");

        pthread_mutex_unlock(&b->lock);
        b->counter = 0;

        if (c->lap % 10 == 0)
            print_scoreboard(run, true);

        b->flag =  lc_continue;

        if (in_linkedlist(run->broken_comp, c->id))
            /*pthread_exit(NULL);*/ printf("broken cyc\n");
    }

    else {
        pthread_mutex_unlock(&b->lock);
        if (in_linkedlist(run->broken_comp, c->id))
            /*pthread_exit(NULL);*/ printf("broken cyc\n");
        while (b->flag != lc_continue);
    }
}

void* thread_cyclist (void *arg) {

    int local_continue = 0;
    cyclist* c = (cyclist*) arg;
    
    while (c->lap <= run->nlaps) {

        pthread_mutex_lock(&track_lock);
        move_cyclist(c, run);
        pthread_mutex_unlock(&track_lock);
        
        if (c->lap != c->dist/run->v->length) {
            c->lap++;

            bool broken = false;

            if (c->lap % 15 == 1)
                broken = break_cyclist(c, run);
            
            if (!broken) {
            
                if (c->lap == (run->nlaps - 2) && run->sprinter == -1) {
                    pthread_mutex_lock(&track_lock);
                    change_speed_90(run);
                    pthread_mutex_unlock(&track_lock);
                }

                else 
                    change_speed(c->id, run);
            }
        }

        hold(local_continue, c);    
    }
    return NULL;
}

void init_race () {
    for (uint i = 0; i < run->ncomp; i++) {
        pthread_create(&run->th_comp[i], NULL, thread_cyclist, (void*)run->comp[i]);
    }
    for (uint i = 0; i < run->ncomp; i++) {
        pthread_join(run->th_comp[i], NULL);
    }
    printf("threads created\n");
}

/* Construct a race with a velodrome* with length as its length,
 * an array of cyclist* with ncomp as the number of competitors and
 * initialize the number of laps in the race */
race* construct_race (uint length, uint ncomp, uint laps) {
    race* r = malloc(sizeof(race));
    r->comp = construct_competitors(ncomp);
    r->v = construct_velodrome(length);
    r->th_comp = malloc(ncomp * sizeof(pthread_t));
    r->sprinter = -1;
    r->broken_comp = construct_linkedlist();
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

/* Free the race* and its fields 
void destroy_race (race* r) {
    destroy_velodrome(r->v);
    destroy_competitors(r->comp, r->ncomp);
    free(r);
}
*/

int main (int argc, char** argv) {
    if (argc != 4) {
        printf("Insufficient number of arguments\n");
        exit(-1);
    }

    srand(time(NULL));

    //interval = 60;
    //timer = 0;
    pthread_mutex_init(&track_lock, NULL);
    b = construct_barrier();
    run = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    printf("start debug\n");
    init_race();
    pthread_mutex_destroy(&track_lock);
    
    return 0;
}