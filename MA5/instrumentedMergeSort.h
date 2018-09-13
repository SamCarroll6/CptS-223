/***************************************************************************
 *
 *  Sorting algorithms and counting work - Merge sort algorithm
 *   Aaron S. Crandall, 2017 <acrandal@gmail.com>
 *   For Educational use only
 *
 *  This .h provides an instrumented mergesort
 *
 */

#ifndef __INSTRUMENTEDMS_H
#define __INSTRUMENTEDMS_H

#include <vector>
#include <ctime>
#include "main.h"   // For SortStats struct definiton

using namespace std;

void instrumentedMergeSort( vector<int> & a, SortStats & stats )
{
    vector<int> hold = a, hold2;
    clock_t time_begin = clock();       // Grab presort time
    if(a.size() == 1)
    return;
    else{
      for (size_t i = 0; i < hold.size() / 2; i++){
        hold2.push_back(hold.back());
        hold.pop_back();
      }
      instrumentedMergeSort(hold, stats);
      instrumentedMergeSort(hold2, stats);
      bool Oorder = true;
      int count = 0, count2 = 0, place = 0;
      while (Oorder){
        if(count == hold.size()){
          while(count2 != hold2.size()){
          a[place] = hold2[count2];
          place++;
          count2++;
          }
          Oorder = false;
        }
        else if(count2 == hold2.size()){
          while(count != hold.size()){
          a[place] = hold[count];
          place++;
          count++;
          }
          Oorder = false;
        }
        else if(++stats.compares && hold[count] < hold2[count2]){
          stats.moves++;
          a[place] = hold[count];
          count++;
        }
        else if(++stats.compares && hold2[count2] <= hold[count]){
          stats.moves++;
          a[place] = hold2[count2];
          count2++;
        }
        place++;
      }
    }


    clock_t time_end = clock();         // Grab time when sort complete
	stats.sortTime = double(time_end - time_begin) / CLOCKS_PER_SEC;
}


#endif
