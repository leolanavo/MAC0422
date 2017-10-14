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
bool debug;
int lap_counter, k_counter, comp_counter, sp_counter;
double interval, timer;
pthread_mutex_t track_lock, break_lock, special_lock, time_lock;
struct timespec ts;

int scores[] = {5, 3, 2, 1};
int scored[4];

bool contains (int id) {
    for (int i = 0; i < 4; i++)
        if (id == scored[i])
            return true;
    
    return false;       
}

int hold (int lc_continue, cyclist* c) {
    lc_continue = (lc_continue == 0) ? 1 : 0;

    pthread_mutex_lock(&b->op_lock);
    int arrived = ++(b->counter);

    if (c->lap == run->nlaps + 1)
        	run->exit++;


    if (arrived == run->ncomp) {

        if (debug) print_tracks(run->v);

        timer = timer + interval;

        int broke = has_cyclist(run->broken_comp);
        if (broke != 0) {
            run->broken_comp->size += broke;
            run->ncomp = run->ncomp - broke;
        }

        if (run->exit != 0) {
        	run->ncomp = run->ncomp - run->exit;
        	run->exit = 0;
        }

        if (run->sprinter >= 0 && run->comp[run->sprinter]->lap == run->nlaps - 1) {
            run->comp[run->sprinter]->speed = 90;
            interval = 20;
        }

        pthread_mutex_unlock(&b->op_lock);

        b->counter = 0;
        b->flag =  lc_continue;

        if (in_linkedlist(run->broken_comp, c->id))            
            pthread_exit(NULL);
    }

    else {

        if (c->lap == lap_counter && k_counter < 4 && !contains(c->id)) {
            scored[k_counter] = c->id;
            c->score += scores[k_counter];
            k_counter++;
        } 

        else if (k_counter == 4) {
            printf(BLUE "SCOREBOARD LAP: %d" RESET "\n", lap_counter);
            print_scoreboard(run, 1, -1);
            printf("\n");
            
            for (int i = 0; i < 4; i++)
                scored[i] = -1;

            lap_counter += 10;
            k_counter = 0;
        }           

        pthread_mutex_unlock(&b->op_lock);
        
        while (b->flag != lc_continue)
            nanosleep(&ts, NULL);

        if (in_linkedlist(run->broken_comp, c->id))
            pthread_exit(NULL);
    }

    return lc_continue;
}

void* thread_cyclist (void *arg) {

    int local_continue = 0;
    cyclist* c = (cyclist*) arg;

    while (c->lap <= run->nlaps) {
        
        pthread_mutex_lock(&track_lock);
        move_cyclist(c, run);
        pthread_mutex_unlock(&track_lock);


        if (c->lap < c->dist/run->v->length) {
            c->lap++;
            
            pthread_mutex_lock(&special_lock);
            if (c->lap == sp_counter) {
                printf(YELLOW "SCORE PER LAP: %d" RESET "\n", sp_counter);
                print_scoreboard(run, 0, -1);
                if (sp_counter >= 3)
                    specialPoints(run);
                sp_counter++;
            }
            pthread_mutex_unlock(&special_lock);


            bool broken = false;

            if (c->lap % 15 == 1) {
                pthread_mutex_lock(&break_lock);
                
                broken = break_cyclist(c, run);
                if (broken)
                    print_scoreboard(run, 1, c->id);
                
                pthread_mutex_unlock(&break_lock);
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
    pthread_mutex_lock(&time_lock);
    c->ftime = timer/60000;
    pthread_mutex_unlock(&time_lock);
    
    return NULL;
}

void init_race () {
    for (int i = 0; i < run->ncomp; i++)
        pthread_create(&run->th_comp[i], NULL, thread_cyclist, (void*)run->comp[i]);

    for (int i = 0; i < run->ncomp; i++)
        pthread_join(run->th_comp[i], NULL);

    for (int i = 0; i < run->fixed_ncomp; i++) {
        bool p = false;
        while (run->comp[i]->speed != 0 && run->comp[i]->ftime == 0)
            if (!p) {
                printf("%d %d %d %.2f %d\n", 
                      i, run->comp[i]->speed, run->comp[i]->lap, run->comp[i]->ftime,
                      run->comp[i]->dist/run->v->length);
                p = true;
            }
    }

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
    r->fixed_ncomp = ncomp;
    return r;
}

barrier* construct_barrier () {
    barrier* b = malloc(sizeof(barrier));
    b->counter = 0;
    b->flag = 0;
    pthread_mutex_init(&b->op_lock, NULL);
    return b;
}

void destroy_barrier() {
    pthread_mutex_destroy(&b->op_lock);
    free(b);
}

/* Free the race* and its fields */
void destroy_race () {
    destroy_array(run->comp, run->fixed_ncomp);
    destroy_velodrome(run->v);
    destroy_linkedlist(run->broken_comp);
    free(run->th_comp);
    free(run);
}

int main (int argc, char** argv) {
    if (argc < 4) {
        printf("Insufficient number of arguments\n");
        exit(-1);
    }

    debug = argc == 5? true: false;

    srand(time(NULL));

    interval = 60.0;
    timer = 0.0;
    lap_counter = 10;
    sp_counter = 2;
    comp_counter = k_counter = 0;
    ts.tv_sec = 0;
    ts.tv_nsec = 600;

    pthread_mutex_init(&track_lock, NULL);
    pthread_mutex_init(&break_lock, NULL);
    pthread_mutex_init(&special_lock, NULL);
    pthread_mutex_init(&time_lock, NULL);

    b = construct_barrier();
    run = construct_race(atof(argv[1]), atoi(argv[2]), atoi(argv[3]));
    for (int i = 0; i < 4; i++)
        scored[i] = -1;

    init_race();
    print_scoreboard(run, 2, -1);
    print_linkedlist(run->broken_comp);

    destroy_race();
    destroy_barrier();
    pthread_mutex_destroy(&track_lock);
    pthread_mutex_destroy(&special_lock);
    pthread_mutex_destroy(&break_lock);
    pthread_mutex_destroy(&time_lock);

    return 0;
}
