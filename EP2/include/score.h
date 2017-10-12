#ifndef SCORE_H
#define SCORE_H

/***********************************************
 * Function: swap                              *
 * --------------                              *
 *  @arg a: the first cyclist                  *
 *  @arg b: the second cyclist                 *
 *                                             *
 *  @process: Swaps to cyclist in the memory   *
 *                                             *
 *  @retrun: void function.                    *
 ***********************************************/
void swap(cyclist *a, cyclist *b);

/********************************************************
 * Function: partition                                  *
 * -------------------                                  *
 *  @arg comp: an array of cyclists                     *
 *  @arg l:    the begging of the subarray              *
 *  @arg r:    the end of the subarray                  *
 *                                                      *
 *  @process:  divides the subarray into two parts,     *
 *             the first one contains all the cyclists  *
 *             which have a smaller dist value, and the *
 *             seconde one, all the bigger.             *
 *                                                      *
 *  @retrun:   the position where the last cyclist      *
 *             in the subarray should be if the array   *
 *             was sorted using the dist field          *
 ********************************************************/
int partition(cyclist** comp, int l, int r);

/***********************************************************
 * Function: kthselec                                      *
 * ------------------                                      *
 *  @arg comp: the array of cyclists                       *
 *  @arg l:    begging of the subarray                     *
 *  @arg r:    end of the subarray                         *
 *  @arg k:    the index of the desired cyclist if the     *
 *             array was sorted using the dist field       *
 *                                                         *
 *  @return:   the kth element in the comp array if it was *
 *             sorted using the dist field                 *
 ***********************************************************/
cyclist* kthselect(cyclist** comp, int l, int r, int k);

/**********************************************************
 * Function: addScore                                     *
 * ------------------                                     *
 *  @arg comp:  the array of cyclists                     *
 *  @arg ncomp: the number of elements in the comp array  *
 *  @arg k:     the index of the desired cyclist if the   *
 *              array was sorted using the dist field     *
 *                                                        *
 *  @process:   select the kth element in the comp array, *
 *              if the array was sorted using the dist    *
 *              field, and adds the number of points      *
 *              that the cyclist deserve.                 *
 *              Returns doing nothing if the k is equal   *
 *              or greater than 5                         *
 *                                                        *
 *  @return:    void function                             *
 **********************************************************/
void addScore (cyclist** comp, int ncomp, int k);

void addScoreSpecial (cyclist** comp, int ncomp);
#endif
