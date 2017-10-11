#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>

#include "types.h"
#include "cyclist.h"
#include "velodrome.h"
#include "linkedlist.h"
#include "scoreboard.h"

race* run;
barrier* b;
//int interval;
//int timer;
pthread_mutex_t track_lock;
struct timespec ts;

int hold (int lc_continue, cyclist* c) {
    lc_continue = (lc_continue == 0) ? 1 : 0;

    pthread_mutex_lock(&b->op_lock);
    int arrived = ++(b->counter);

    if (c->lap == run->nlaps + 1)
        	run->exit++;


    if (arrived == run->ncomp) {
        printf(YELLOW "FINAL HOLDER LAP: %d ID: %d" RESET "\n", c->lap, c->id);
        //print_tracks(run->v);

        //if (c->lap % 10 == 0)
            /*print_scoreboard(run, true);*/

        int broke = has_cyclist(run->broken_comp);

        if (broke != 0)
            printf(" number of broken cyc %d\n", broke);
        run->ncomp = run->ncomp - broke;

        print_linkedlist(run->broken_comp);

        if (run->exit != 0) {
        	run->ncomp = run->ncomp - run->exit;
        	run->exit = 0;
        }

        pthread_mutex_unlock(&b->op_lock);

        b->counter = 0;
        b->flag =  lc_continue;

        if (in_linkedlist(run->broken_comp, c->id)) {
            printf("BROKEN CYC\n");
            pthread_exit(NULL);
        }
    }

    else {

        pthread_mutex_unlock(&b->op_lock);
        
        while (b->flag != lc_continue){
            nanosleep(&ts, NULL);
        }

        if (in_linkedlist(run->broken_comp, c->id)) {
            printf("broken cyc id %d\n", c->id);
            pthread_exit(NULL);
        }

        while (b->flag != lc_continue) nanosleep(&ts, NULL);
    }

    return lc_continue;
}

void* thread_cyclist (void *arg) {

    int local_continue = 0;
    cyclist* c = (cyclist*) arg;

    while (c->lap <= run->nlaps) {

        move_cyclist(c, run);
        //printf( CYAN "ID: %d DIST: %d FRACTION: %d " RESET "\n", c->id, c->dist, c->dist/run->v->length);


        if (c->lap < c->dist/run->v->length) {
            c->lap++;
            bool broken = false;

            if (c->lap % 15 == 1) {
                pthread_mutex_lock(&track_lock);
                broken = break_cyclist(c, run);
                pthread_mutex_unlock(&track_lock);

            }

            if (!broken) {

                if (c->lap == (run->nlaps - 2) && run->sprinter == -1)
                    change_speed_90(run);
                else
                    change_speed(c->id, run);
            }
        }

        local_continue = hold(local_continue, c);
    }
    return NULL;
}

void init_race () {
    for (int i = 0; i < run->ncomp; i++) {
        pthread_create(&run->th_comp[i], NULL, thread_cyclist, (void*)run->comp[i]);
    }

    for (int i = 0; i < run->ncomp; i++) {
        pthread_join(run->th_comp[i], NULL);
    }

    printf("threads created\n");
}

/* Construct a race with a velodrome* with length as its length,
 * an array of cyclist* with ncomp as the number of competitors and
 * initialize the number of laps in the race */
race* construct_race (int length, int ncomp, int laps) {
    race* r = malloc(sizeof(race));
    r->comp = construct_competitors(ncomp);
    r->v = construct_velodrome(length, ncomp, r->comp);
    r->th_comp = malloc(ncomp * sizeof(pthread_t));
    r->sprinter = -1;
    r->broken_comp = construct_linkedlist();
    r->exit = 0;
    r->nlaps = laps;
    r->ncomp = ncomp;
    return r;
}

barrier* construct_barrier () {
    barrier* b = malloc(sizeof(barrier));
    b->counter = 0;
    b->flag = 0;
    pthread_mutex_init(&b->op_lock, NULL);
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
    ts.tv_sec = 0;
    ts.tv_nsec = 600;

    pthread_mutex_init(&track_lock, NULL);
    init_mutex();
    b = construct_barrier();
    run = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    init_race();
    pthread_mutex_destroy(&track_lock);

    return 0;
}
